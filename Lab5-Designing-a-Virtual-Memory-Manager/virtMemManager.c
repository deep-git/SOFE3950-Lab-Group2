
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

struct tlbinput_value {
    unsigned char logiAddress;
    unsigned char physAddress;
};

struct tlbinput_value tlb[TLB_SIZE];

signed char main_memory[MEMORY_SIZE];
char buffer[BUFFER_SIZE];

int tlb_index = 0;
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
    struct tlbinput_value *input_value = &tlb[tlb_index % TLB_SIZE];
    tlb_index++;
    input_value->logiAddress = logical;
    input_value->physAddress = physical;
}

// Returns the physical address from TLB or -1 if not present.
int search_tlb(unsigned char logicalPage) {
    int i;
    for (i = max((tlb_index - TLB_SIZE), 0); i < tlb_index; i++) {
        struct tlbinput_value *input_value = &tlb[i % TLB_SIZE];

        if (input_value->logiAddress == logicalPage) {
            return input_value->physAddress;
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


    const char *backing_store_file = argv[1];
    int backing_fd = open(backing_store_file, O_RDONLY);
    backing = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, backing_fd, 0);

    const char *input_file = argv[2];
    FILE *input_fp = fopen(input_file, "r");

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
        int logicalAddress = atoi(buffer);
        int offset = logicalAddress & OFFSET_MASK;
        int logicalPage= (logicalAddress >> OFFSET_BITS) & PAGE_MASK;
        int physicalPage = search_tlb(logicalPage);

        if (physicalPage != -1) {                          // TLB hit
            tlb_hits++;

        } else {                                            // TLB miss
            physicalPage = pagetable[logicalPage];

            if (physicalPage == -1) {                      // Page fault
                page_faults++;
                physicalPage = free_page;
                free_page++;

                // Copy page from backing file into physical memory
                memcpy(main_memory + physicalPage * PAGE_SIZE, backing + logicalPage * PAGE_SIZE, PAGE_SIZE);

                pagetable[logicalPage] = physicalPage;
            }

            add_to_tlb(logicalPage, physicalPage);
        }

        int physicalAddress = (physicalPage << OFFSET_BITS) | offset;
        signed char value = main_memory[physicalPage * PAGE_SIZE + offset];

        printf("Virtual address: %d \tPhysical address: %d \tValue: %d\n", logicalAddress, physicalAddress, value);
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
