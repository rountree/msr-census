// SPDX-License-Identifier: GPL-2.0

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cpu.h>

static int __init census_init(void)
{
	int rc;
	u32 reg;
	u32 data[2];
	struct cpuinfo_x86 *c = &cpu_data(0);

	printk( KERN_INFO "msr-census CPU vendor 0x%x family 0x%x model 0x%x stepping 0x%x\n",
			c->x86_vendor, c->x86, c->x86_model, c->x86_stepping );
	for( reg=0; reg<0x10000; reg++ ){
		rc = rdmsr_safe_on_cpu(0, reg, &data[0], &data[1]);
		if( rc==0 ){
			printk( KERN_INFO "msr-census register 0x%x value 0x%llx\n", reg, data[0] | ((u64)(data[1]) << 32) );
		}
	}
	for( reg=0xc0000000; reg<0xc0010000; reg++ ){
		if( rc==0 ){
			printk( KERN_INFO "msr-census register 0x%x value 0x%llx\n", reg, data[0] | ((u64)(data[1]) << 32) );
		}
	}
	return 0;
}

static void __exit census_exit(void){
	printk( KERN_INFO "msr-census:  unloaded.\n");
}

module_init(census_init);
module_exit(census_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Barry Rountree <rountree@llnl.gov>");
