#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "/usr/include/ext2fs/ext2_fs.h"

#define BASE_OFFSET 1024      /* locates beginning of the super block (first group) */
#define RD_DEVICE "/dev/ram0" /* the floppy disk device */
#define BLOCK_OFFSET(block) (block_size + (block - 1) * block_size)
#define I_ROOT (2)

static unsigned int block_size = 0; /* block size (to be calculated) */

static unsigned int read_dir(int, const struct ext2_inode *, const struct ext2_group_desc *, const char *);
static void read_inode(int, int, const struct ext2_group_desc *, struct ext2_inode *);
static int FindFile(const char *path_ram0, const char *path_file, char *ret_val);
static void ReadSuperBlock(int ramdisk, struct ext2_super_block *super);
static void ReadGroupDesc(int ramdisk, struct ext2_group_desc *group, unsigned int block_size);
static int FindFileRecursive(const char *path_ram0, const char *path_file, char *buffer);

int main()
{
    int ret_val = 0;
    char buffer[1000] = {0};

    if (0 != FindFileRecursive(RD_DEVICE, "child_dir/grand_child_dir/grand_grand_child_dir/content.txt", buffer))
    {
        printf("error occurred  \n");
        return 1;
    }
    else
    {
        printf("file content: %s\n", buffer);
    }

    return 0;
}

static int FindFileRecursive(const char *path_ram0, const char *path_file, char *buffer)
{
    struct ext2_super_block super;
    struct ext2_group_desc group;
    struct ext2_inode inode;
    int inode_index = I_ROOT;
    int ramdisk = 0;
    ssize_t status = 0;
    char *token;
    char str[100];

    strcpy(str, path_file);

    /* open device */
    if ((ramdisk = open(path_ram0, O_RDONLY)) < 0)
    {
        perror(RD_DEVICE);
        exit(1); /* error while opening the device */
    }

    /* read super-block */
    ReadSuperBlock(ramdisk, &super);

    block_size = 1024 << super.s_log_block_size;
    printf("super.s_log_block_size %d\n", super.s_log_block_size);
    /* read group descriptor */
    ReadGroupDesc(ramdisk, &group, block_size);
    printf("group.bg_inode_table %d\n", group.bg_inode_table);
    read_inode(ramdisk, inode_index, &group, &inode);

    /* show entries in the root directory */
    token = strtok(str, "/");
    while (token != NULL)
    {
        printf(" %s\n", token);
        inode_index = read_dir(ramdisk, &inode, &group, token);
        read_inode(ramdisk, inode_index, &group, &inode);
        token = strtok(NULL, "/");
    }

    lseek(ramdisk, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET);
    status = read(ramdisk, buffer, 1000);

    if (status <= 0)
    {
        return 1;
    }

    return 0;
}

static int FindFile(const char *path_ram0, const char *path_file, char *buffer)
{
    struct ext2_super_block super;
    struct ext2_group_desc group;
    struct ext2_inode inode;
    int inode_index = I_ROOT;
    int ramdisk = 0;
    ssize_t status = 0;

    /* open floppy device */
    if ((ramdisk = open(path_ram0, O_RDONLY)) < 0)
    {
        perror(RD_DEVICE);
        exit(1); /* error while opening the floppy device */
    }

    /* read super-block */
    ReadSuperBlock(ramdisk, &super);

    block_size = 1024 << super.s_log_block_size;
    printf("super.s_log_block_size %d\n", super.s_log_block_size);
    /* read group descriptor */
    ReadGroupDesc(ramdisk, &group, block_size);
    printf("group.bg_inode_table %d\n", group.bg_inode_table);
    /* show entries in the root directory */
    read_inode(ramdisk, inode_index, &group, &inode);
    inode_index = read_dir(ramdisk, &inode, &group, path_file);
    printf("inode_index %d\n", inode_index);
    read_inode(ramdisk, inode_index, &group, &inode);
    lseek(ramdisk, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET);
    status = read(ramdisk, buffer, 1000);
    printf("inode_index %d\n", inode_index);
    if (status <= 0)
    {
        return 1;
    }

    return 0;
}

static void ReadGroupDesc(int ramdisk, struct ext2_group_desc *group, unsigned int block_size)
{
    lseek(ramdisk, block_size, SEEK_SET);
    read(ramdisk, group, sizeof(*group));
}

static void ReadSuperBlock(int ramdisk, struct ext2_super_block *super)
{
    printf("ReadSuperBlock\n");
    lseek(ramdisk, BASE_OFFSET, SEEK_SET);
    read(ramdisk, super, sizeof(*super));
    if (super->s_magic != EXT2_SUPER_MAGIC)
    {
        fprintf(stderr, "Not a Ext2 filesystem\n");
        exit(1);
    }
}

static void read_inode(int fd, int inode_no, const struct ext2_group_desc *group, struct ext2_inode *inode)
{
    printf("read_inode\n");
    lseek(fd, BLOCK_OFFSET(group->bg_inode_table) + (inode_no - 1) * sizeof(struct ext2_inode),
          SEEK_SET);
    read(fd, inode, sizeof(struct ext2_inode));
} /* read_inode() */

static unsigned int read_dir(int fd, const struct ext2_inode *inode, const struct ext2_group_desc *group,
                             const char *str)
{
    void *block;
    char ch = 0;
    char buffer[100] = {0};
    size_t ret = 0;

    if (S_ISDIR(inode->i_mode))
    {
        struct ext2_dir_entry_2 *entry;
        unsigned int size = 0;

        if ((block = malloc(block_size)) == NULL)
        { /* allocate memory for the data block */
            fprintf(stderr, "Memory error\n");
            close(fd);
            exit(1);
        }

        lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
        read(fd, block, block_size); /* read block from disk*/

        entry = (struct ext2_dir_entry_2 *)block; /* first entry in the directory */
                                                  /* Notice that the list may be terminated with a NULL
                                                     entry (entry->inode == NULL)*/
        while ((size < inode->i_size) && entry->inode)
        {
            char file_name[EXT2_NAME_LEN + 1];
            memcpy(file_name, entry->name, entry->name_len);
            file_name[entry->name_len] = 0; /* append null character to the file name */
            printf("%10u %s\n", entry->inode, file_name);
            if (0 == strcmp(file_name, str))
            {
                return entry->inode;
            }
            entry = (void *)entry + entry->rec_len;
            size += entry->rec_len;
        }

        free(block);

        return entry->inode;
    }

    return 0;
} /* read_dir() */
