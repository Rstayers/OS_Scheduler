#define IA32_EFER 0xC0000080
#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_ENABLE 0x800

#define APIC_LVT_TIMER 0x320
#define APIC_TIMER_DIV 0x3e0
#define DIV_1   13
#define DIV_128 12
#define APIC_TIMER_SET 0x380
#define APIC_TIMER_GET 0x390

/* COM1 */
#define SERIAL_PORT 0x3f8

#define PCI_ADDR_PORT 0xcf8
#define PCI_DATA_PORT 0xcfc


#define PIT_CTRL 0x43
#define PIT_CHAN0 0x40
