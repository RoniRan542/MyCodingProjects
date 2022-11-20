/*
 * ext2super.c
 *
 * Reads the super-block from a Ext2 floppy disk.
 *
 * Questions?
 * Emanuele Altieri
 * ealtieri@hampshire.edu
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "/usr/include/ext2fs/ext2_fs.h"

#define BASE_OFFSET 1024 /* locates beginning of the super block (first group) */
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block - 1) * block_size)

#define ramdisk_DEVICE "/dev/ram0"

static unsigned int block_size = 0; /* block size (to be calculated) */

int main(void)
{
    struct ext2_super_block super;
    struct ext2_group_desc group;
    unsigned int inodes_per_block = 0;
    unsigned int itable_blocks = 0;
    unsigned char *bitmap;
    int ramdisk;

    bitmap = malloc(block_size); /* allocate memory for the bitmap */
    lseek(ramdisk, BLOCK_OFFSET(group.bg_block_bitmap), SEEK_SET);
    read(ramdisk, bitmap, block_size); /* read bitmap from disk */
    /* printf("bitmap %d\n", *bitmap); */
    free(bitmap);
    /* open floppy device */
    if ((ramdisk = open(ramdisk_DEVICE, O_RDONLY)) < 0)
    {
        perror(ramdisk_DEVICE);
        exit(1); /* error while opening the floppy device */
    }

    /* read super-block */

    lseek(ramdisk, BASE_OFFSET, SEEK_SET);
    read(ramdisk, &super, sizeof(super));

    if (super.s_magic != EXT2_SUPER_MAGIC)
    {
        fprintf(stderr, "Not a Ext2 filesystem\n");
        exit(1);
    }

    block_size = 1024 << super.s_log_block_size;

    /* calculate number of block groups on the disk */
    unsigned int group_count = 1 + (super.s_blocks_count - 1) / super.s_blocks_per_group;

    /* calculate size of the group descriptor list in bytes */
    unsigned int descr_list_size = group_count * sizeof(struct ext2_group_desc);

    printf("group_count %d\n", group_count);
    printf("descr_list_size %d\n", descr_list_size);
    /* read group descriptor */

    lseek(ramdisk, block_size, SEEK_SET);
    read(ramdisk, &group, sizeof(group));
    close(ramdisk);

    printf("Reading first group-descriptor from device " ramdisk_DEVICE ":\n"
           "the \n"
           "Bg_inode_table: %u\n"
           "Blocks bitmap block: %u\n"
           "Inodes bitmap block: %u\n"
           "Inodes table block : %u\n"
           "Free blocks count  : %u\n"
           "Free inodes count  : %u\n"
           "Directories count  : %u\n",
           group.bg_inode_table,
           group.bg_block_bitmap,
           group.bg_inode_bitmap,
           group.bg_inode_table,
           group.bg_free_blocks_count,
           group.bg_free_inodes_count,
           group.bg_used_dirs_count); /* directories count */

    /* number of inodes per block */

    inodes_per_block = block_size / sizeof(struct ext2_inode);

    /* size in blocks of the inode table */
    itable_blocks = super.s_inodes_per_group / inodes_per_block;

    printf("inodes_per_block %d\n", inodes_per_block);
    printf("itable_blocks %d\n", itable_blocks);

    exit(0);
} /* main() */