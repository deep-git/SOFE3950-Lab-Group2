
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define TLB_SIZE 16

#define PAGES 256
#define PAGE_MASK 255
#define PAGE_SIZE 256

#define OFFSET_BITS 8
#define OFFSET_MASK 255

#define MEMORY_SIZE PAGES * PAGE_SIZE
#define BUFFER_SIZE 10

struct tlbentry {
    unsigned char logiAddress;
    unsigned char physAddress;
};

struct tlbentry tlb[TLB_SIZE];

signed char main_memory[MEMORY_SIZE];
char buffer[BUFFER_SIZE];

int tlbindex = 0;
int pagetable[PAGES];
signed char *backing;

// find max
int max(int a, int b){
    if (a > b)
        return a;
    return b;
}

// FIFO
void add_to_tlb(unsigned char logical, unsigned char physical) {
    struct tlbentry *entry = &tlb[tlbindex % TLB_SIZE];
    tlbindex++;
    entry->logiAddress = logical;
    entry->physAddress = physical;
}

// Returns the physical address from TLB or -1 if not present. 
int search_tlb(unsigned char logical_page) {
    int i;
    for (i = max((tlbindex - TLB_SIZE), 0); i < tlbindex; i++) {
        struct tlbentry *entry = &tlb[i % TLB_SIZE];
        
        if (entry->logiAddress == logical_page) {
            return entry->physAddress;
        }
    }
    
    return -1;
}

int main(int argc, const char *argv[]){
    //invalid usage 
    if (argc != 3) {
        printf("----------------------------------------------------\n");
        printf("USAGE: ./virtMemManager BACKING_STORE.bin <filename>\n");
        printf("----------------------------------------------------\n");
        exit(0);
    }
    
    printf("***********************************************************\n");


    const char *backing_filename = argv[1]; 
    int backing_fd = open(backing_filename, O_RDONLY);
    backing = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, backing_fd, 0); 
    
    const char *input_filename = argv[2];
    FILE *input_fp = fopen(input_filename, "r");
    
    // initialize page table
    int i;
    for (i = 0; i < PAGES; i++) {
        pagetable[i] = -1;
    }
        
    // integers for calculating stats
    int total_addresses = 0;
    int tlb_hits = 0;
    int page_faults = 0;
    
    // Number of the next unallocated physical page in main memory
    unsigned char free_page = 0;
    
    // read address file
    while (fgets(buffer, BUFFER_SIZE, input_fp) != NULL) {
        total_addresses++;
        int logical_address = atoi(buffer);
        int offset = logical_address & OFFSET_MASK;
        int logical_page = (logical_address >> OFFSET_BITS) & PAGE_MASK;
        int physical_page = search_tlb(logical_page);

        if (physical_page != -1) {                          // TLB hit
            tlb_hits++; 
            
        } else {                                            // TLB miss
            physical_page = pagetable[logical_page];        
            
            if (physical_page == -1) {                      // Page fault
                page_faults++;
                physical_page = free_page;
                free_page++;
                
                // Copy page from backing file into physical memory
                memcpy(main_memory + physical_page * PAGE_SIZE, backing + logical_page * PAGE_SIZE, PAGE_SIZE);
                
                pagetable[logical_page] = physical_page;
            }
            
            add_to_tlb(logical_page, physical_page);
        }
        
        int physical_address = (physical_page << OFFSET_BITS) | offset;
        signed char value = main_memory[physical_page * PAGE_SIZE + offset];
        
        printf("Virtual address: %d \tPhysical address: %d \tValue: %d\n", logical_address, physical_address, value);
    }
    
    double page_fault_rate = page_faults / (1. * total_addresses);
    double tlb_hit_rate = tlb_hits / (1. * total_addresses);


    // print 
    printf("***********************************************************\n");
    printf("Number of Translated Addresses \t= %d\n", total_addresses);
    printf("Page Faults \t\t\t= %d\n"                   , page_faults);
    printf("Page Fault Rate \t\t= %.3f\n"             , page_fault_rate);
    printf("TLB Hits \t\t\t= %d\n"                      , tlb_hits);
    printf("TLB Hit Rate \t\t\t= %.3f\n"                , tlb_hit_rate);
    
    return 0;
}
