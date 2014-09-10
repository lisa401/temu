/*
** The Sleuth Kit 
**
** $Date: 2006/03/22 03:44:58 $
**
** Brian Carrier [carrier@sleuthkit.org]
** Copyright (c) 2003-2005 Brian Carrier.  All rights reserved
**
** TASK
** Copyright (c) 2002 @stake Inc.  All rights reserved
*/
#ifndef _FFS_H
#define _FFS_H

#ifdef __cplusplus
extern "C" {
#endif

    extern uint8_t
	ffs_dent_walk(FS_INFO *, INUM_T, int, FS_DENT_WALK_FN, void *);


    typedef uint32_t FFS_GRPNUM_T;
#define PRI_FFSGRP PRIu32

/*
** CONSTANTS
**/
#define FFS_FIRSTINO	0	/* 0 & 1 are reserved (1 was bad blocks) */
#define FFS_ROOTINO		2	/* location of root directory inode */
#define FFS_NDADDR		12
#define FFS_NIADDR		3

#define UFS1_SBOFF	8192
#define UFS2_SBOFF	65536
#define UFS2_SBOFF2	262144

#define UFS1_FS_MAGIC	0x011954
#define UFS2_FS_MAGIC	0x19540119

#define FFS_MAXNAMLEN 	255
#define FFS_MAXPATHLEN	1024
#define FFS_DIRBLKSIZ	512



#define FFS_DEV_BSIZE	512


    typedef struct {
	uint8_t dir_num[4];
	uint8_t blk_free[4];
	uint8_t ino_free[4];
	uint8_t frag_free[4];
    } ffs_csum1;

    typedef struct {
	uint8_t dir_num[8];
	uint8_t blk_free[8];
	uint8_t ino_free[8];
	uint8_t frag_free[8];
	uint8_t clust_free[8];
	uint8_t f1[24];
    } ffs_csum2;



/*
 * Super Block Structure
 */

// UFS 1
    typedef struct {
	uint8_t f1[8];
	/* Offsets in each cylinder group */
	uint8_t sb_off[4];	/* s32 */
	uint8_t gd_off[4];	/* s32 */
	uint8_t ino_off[4];	/* s32 */
	uint8_t dat_off[4];	/* s32 */

	/* How much the base of the admin data in each cyl group changes */
	uint8_t cg_delta[4];	/* s32 */
	uint8_t cg_cyc_mask[4];	/* s32 */

	uint8_t wtime[4];	/* u32 : last written time */
	uint8_t frag_num[4];	/* s32 - number of fragments in FS */
	uint8_t data_frag_num[4];	/* s32 - number of frags not being used for admin data */
	uint8_t cg_num[4];	/* s32 - number of cyl grps in FS */

	uint8_t bsize_b[4];	/* s32 - size of block */
	uint8_t fsize_b[4];	/* s32 - size of fragment */
	uint8_t bsize_frag[4];	/* s32 - num of frag in block */
	uint8_t f5[36];
	uint8_t fs_fragshift[4];	/* s32 */
	uint8_t f6[20];
	uint8_t fs_inopb[4];	/* s32 */
	uint8_t f7[20];
	uint8_t fs_id[8];
	uint8_t cg_saddr[4];	/* s32 */
	uint8_t cg_ssize_b[4];	/* s32 */
	uint8_t fs_cgsize[4];	/* s32 */
	uint8_t f7c[12];
	uint8_t fs_ncyl[4];	/* s32 */
	uint8_t fs_cpg[4];	/* s32 */
	uint8_t cg_inode_num[4];	/* s32 */
	uint8_t cg_frag_num[4];	/* s32 */

	ffs_csum1 cstotal;

	uint8_t fs_fmod;
	uint8_t fs_clean;
	uint8_t fs_ronly;
	uint8_t fs_flags;
	uint8_t last_mnt[512];
	uint8_t f8[648];
	uint8_t magic[4];	/* s32 */
	uint8_t f9[160];	/* filler so it is a multiple of 512 */
    } ffs_sb1;


// UFS 2
    typedef struct {
	uint8_t f0[8];
	/* Offsets in each cylinder group */
	uint8_t sb_off[4];	/* s32 */
	uint8_t gd_off[4];	/* s32 */
	uint8_t ino_off[4];	/* s32 */
	uint8_t dat_off[4];	/* s32 */

	uint8_t f1[20];		/* s32 */

	uint8_t cg_num[4];	/* s32 - number of cyl grps in FS */
	uint8_t bsize_b[4];	/* s32 - size of block */
	uint8_t fsize_b[4];	/* s32 - size of fragment */
	uint8_t bsize_frag[4];	/* s32 - num of frag in block */
	uint8_t f2[36];
	uint8_t fs_fragshift[4];	/* s32 */
	uint8_t f3[20];
	uint8_t fs_inopb[4];	/* s32 */
	uint8_t f4[32];
	uint8_t cg_ssize_b[4];	/* s32 */
	uint8_t fs_cgsize[4];	/* s32 */
	uint8_t f5[20];
	uint8_t cg_inode_num[4];	/* s32 */
	uint8_t cg_frag_num[4];	/* s32 - fs_fpg */

	uint8_t f6[16];
	uint8_t fs_fmod;
	uint8_t fs_clean;
	uint8_t fs_ronly;
	uint8_t f7;
	uint8_t last_mnt[468];
	uint8_t volname[32];
	uint8_t swuid[8];
	uint8_t f8[288];

	ffs_csum2 cstotal;

	uint8_t wtime[8];	/* u32 : last written time */
	uint8_t frag_num[8];	/* s32 - number of fragments in FS */
	uint8_t blk_num[8];	/* s32 - number of blocks in FS */
	uint8_t cg_saddr[8];

	uint8_t f9[208];
	uint8_t fs_flags[4];
	uint8_t f10[56];

	uint8_t magic[4];	/* s32 */
	uint8_t f11[160];	/* filler so it is a multiple of 512 */
    } ffs_sb2;


#define FFS_SB_FLAG_UNCLEAN	0x01
#define FFS_SB_FLAG_SOFTDEP	0x02
#define FFS_SB_FLAG_NEEDFSCK	0x04
#define FFS_SB_FLAG_INDEXDIR	0x08
#define FFS_SB_FLAG_ACL		0x10
#define FFS_SB_FLAG_MULTILABEL	0x20
#define FFS_SB_FLAG_UPDATED	0x80


/* How the file system is optimized */
#define FFS_SB_OPT_TIME		0
#define FFS_SB_OPT_SPACE	1



/*
 * Cylinder Group Descriptor
 *
 * UFS1 and UFS2 are the same for the data that we care about unless we 
 * want the wtime for 'fsstat'.  
 */
    typedef struct {
	uint8_t f1[4];
	uint8_t magic[4];	/* 0x090255 */
	uint8_t wtime[4];	/* last written time */
	uint8_t cg_cgx[4];	/* s32 - my group number */
	uint8_t cyl_num[2];	/* number of cyl in this group */
	uint8_t ino_num[2];	/* number of inodes in this group */
	uint8_t frag_num[4];	/* number of fragments in this group */
	ffs_csum1 cs;
	uint8_t last_alloc_blk[4];	/* last allocated blk relative to start */
	uint8_t last_alloc_frag[4];	/* last alloc frag relative to start */
	uint8_t last_alloc_ino[4];
	uint8_t avail_frag[8][4];
	uint8_t f2b[8];
	uint8_t cg_iusedoff[4];	/* s32 */
	uint8_t cg_freeoff[4];	/* s32 */
	uint8_t f3[72];
    } ffs_cgd;

    typedef struct {
	uint8_t f1[4];
	uint8_t magic[4];	/* 0x090255 */
	uint8_t f2[4];
	uint8_t cg_cgx[4];	/* s32 - my group number */
	uint8_t f2a[4];		/* number of cyl in this group */
	uint8_t frag_num[4];	/* number of fragments in this group */
	ffs_csum1 cs;
	uint8_t last_alloc_blk[4];	/* last allocated blk relative to start */
	uint8_t last_alloc_frag[4];	/* last alloc frag relative to start */
	uint8_t last_alloc_ino[4];
	uint8_t avail_frag[8][4];
	uint8_t f2b[8];
	uint8_t cg_iusedoff[4];	/* s32 */
	uint8_t cg_freeoff[4];	/* s32 */

	uint8_t cg_nextfreeoff[4];
	uint8_t cg_clustersumoff[4];
	uint8_t cg_clusteroff[4];
	uint8_t cg_nclustersblks[4];
	uint8_t cg_niblk[4];
	uint8_t cg_initediblk[4];
	uint8_t f3a[12];
	uint8_t wtime[8];
	uint8_t f3[24];
    } ffs_cgd2;


/*
 * inode
 */

/* ffs_inode1: OpenBSD & FreeBSD etc. */
    typedef struct {
	uint8_t di_mode[2];	/* u16 */
	uint8_t di_nlink[2];	/* s16 */
	uint8_t f1[4];
	uint8_t di_size[8];	/* u64 */
	uint8_t di_atime[4];	/* s32 */
	uint8_t di_atimensec[4];
	uint8_t di_mtime[4];	/* s32 */
	uint8_t di_mtimensec[4];
	uint8_t di_ctime[4];	/* s32 */
	uint8_t di_ctimensec[4];
	uint8_t di_db[12][4];	/* s32 */
	uint8_t di_ib[3][4];	/* s32 */
	uint8_t f5[8];
	uint8_t gen[4];
	uint8_t di_uid[4];	/* u32 */
	uint8_t di_gid[4];	/* u32 */
	uint8_t f6[8];
    } ffs_inode1;

/* ffs_inode1b: Solaris */
    typedef struct {
	uint8_t di_mode[2];	/* u16 */
	uint8_t di_nlink[2];	/* s16 */
	uint8_t f1[4];
	uint8_t di_size[8];	/* u64 */
	uint8_t di_atime[4];	/* s32 */
	uint8_t f2[4];
	uint8_t di_mtime[4];	/* s32 */
	uint8_t f3[4];
	uint8_t di_ctime[4];	/* s32 */
	uint8_t f4[4];
	uint8_t di_db[12][4];	/* s32 */
	uint8_t di_ib[3][4];	/* s32 */
	uint8_t f5[16];
	uint8_t di_uid[4];	/* u32 */
	uint8_t di_gid[4];	/* u32 */
	uint8_t f6[4];
    } ffs_inode1b;

    typedef struct {
	uint8_t di_mode[2];	/* u16 */
	uint8_t di_nlink[2];	/* s16 */
	uint8_t di_uid[4];
	uint8_t di_gid[4];
	uint8_t di_blksize[4];	/* u32 inode block size */
	uint8_t di_size[8];	/* u64 */
	uint8_t di_blocks[8];	/* u64 - bytes held */
	uint8_t di_atime[8];	/* s64 */
	uint8_t di_mtime[8];	/* s64 */
	uint8_t di_ctime[8];	/* s64 */
	uint8_t di_crtime[8];	/* s64 */
	uint8_t di_mtimensec[4];	/* s32 */
	uint8_t di_atimensec[4];
	uint8_t di_ctimensec[4];
	uint8_t di_crtimensec[4];
	uint8_t di_gen[4];	/* s32 generation number */
	uint8_t di_kflags[4];	/* u32 kernel flags */
	uint8_t di_flags[4];	/* u32 flags */
	uint8_t di_extsize[4];	/* s32 size of ext attributes block */
	uint8_t di_extb[2][8];	/* Address of ext attribute blocks */
	uint8_t di_db[12][8];	/* s32 */
	uint8_t di_ib[3][8];	/* s32 */
	uint8_t f2[24];		/* s32 */
    } ffs_inode2;

#define FFS_IN_FMT       0170000	/* Mask of file type. */
#define FFS_IN_FIFO      0010000	/* Named pipe (fifo). */
#define FFS_IN_CHR       0020000	/* Character device. */
#define FFS_IN_DIR       0040000	/* Directory file. */
#define FFS_IN_BLK       0060000	/* Block device. */
#define FFS_IN_REG       0100000	/* Regular file. */
#define FFS_IN_LNK       0120000	/* Symbolic link. */
#define FFS_IN_SHAD		 0130000	/* SOLARIS ONLY */
#define FFS_IN_SOCK      0140000	/* UNIX domain socket. */
#define FFS_IN_WHT       0160000	/* Whiteout. */



    typedef struct {
	uint8_t reclen[4];
	uint8_t nspace;
	uint8_t contpad;
	uint8_t nlen;
	uint8_t name[1];	/* of length nlen and padded so contents are on 8-byte boundary */

    } ffs_extattr;

#define FFS_ATTR_CONT(x)	\
  ((((x) + 7 + 7) / 8) * 2)


/*
 * Directory Entries
 */
/* ffs_dentry1: new OpenBSD & FreeBSD etc. */
    typedef struct {
	uint8_t d_ino[4];	/* u32 */
	uint8_t d_reclen[2];	/* u16 */
	uint8_t d_type;		/* u8 */
	uint8_t d_namlen;	/* u8 */
	char d_name[256];
    } ffs_dentry1;

/* type field values */
#define FFS_DT_UNKNOWN   0
#define FFS_DT_FIFO      1
#define FFS_DT_CHR       2
#define FFS_DT_DIR       4
#define FFS_DT_BLK       6
#define FFS_DT_REG       8
#define FFS_DT_LNK      10
#define FFS_DT_SOCK     12
#define FFS_DT_WHT      14

/* ffs_dentry2: Solaris and old xBSDs (no type field) */
    typedef struct {
	uint8_t d_ino[4];	/* u32 */
	uint8_t d_reclen[2];	/* u16 */
	uint8_t d_namlen[2];	/* u16 */
	char d_name[256];
    } ffs_dentry2;


#define FFS_DIRSIZ_lcl(len) \
    ((len + 8 + 3) & ~(3))






/* modified macros */

/* original:
** cgbase(fs, c)   ((daddr_t)((fs)->fs_cg_frag_num * (c)))
*/
#define cgbase_lcl(fsi, fs, c)	\
	((DADDR_T)(gets32(fsi, (fs)->cg_frag_num) * (c)))


/* Macros to calc the locations of structures in cyl groups */

#define cgstart_lcl(fsi, fs, c)                          \
	((DADDR_T)((getu32((fsi), (fs)->magic) == UFS2_FS_MAGIC) ? \
	(cgbase_lcl(fsi, fs, c)) :  \
	(cgbase_lcl(fsi, fs, c) + gets32((fsi), (fs)->cg_delta) * \
	 ((c) & ~(gets32((fsi), (fs)->cg_cyc_mask)))) ))

/* cyl grp block */
#define cgtod_lcl(fsi, fs, c)	\
	((DADDR_T)(cgstart_lcl(fsi, fs, c) + gets32(fsi, (fs)->gd_off)))

/* inode block in cyl grp */
#define cgimin_lcl(fsi, fs, c)	\
	((DADDR_T)(cgstart_lcl(fsi, fs, c) + gets32(fsi, (fs)->ino_off)))

/* 1st data  block in cyl grp*/
#define cgdmin_lcl(fsi, fs, c)   \
	((DADDR_T)(cgstart_lcl(fsi, fs, c) + gets32(fsi, (fs)->dat_off)))

/* super blk in cyl grp*/
#define cgsblock_lcl(fsi, fs, c) 	\
	((DADDR_T)(cgstart_lcl(fsi, fs, c) + gets32(fsi, (fs)->sb_off)))

/* original:
** blkstofrags(fs, blks)  
**    ((blks) << (fs)->fs_fragshift)
*/
#define blkstofrags_lcl(fsi, fs, blks)  \
    ((blks) << gets32(fsi, (fs)->fs_fragshift))

/* original:
** itod(fs, x) \
**      ((DADDR_T)(cgimin(fs, itog(fs, x)) + \
**      (blkstofrags((fs), (((x)%(ulong_t)(fs)->cg_inode_num)/(ulong_t)INOPB(fs))))))
*/
#define itod_lcl(fsi, fs, x) \
      ((DADDR_T)(cgimin_lcl(fsi, fs, itog_lcl(fsi, fs, x)) + \
      (blkstofrags_lcl(fsi, (fs), (((x)%(ULONG)gets32(fsi, (fs)->cg_inode_num))/ \
	  (ULONG)gets32(fsi, (fs)->fs_inopb))))))

/* original:
** itoo(fs, x) ((x) % (uint32_t)INOPB(fs))
*/
#define itoo_lcl(fsi, fs, x) 	\
	((x) % (uint32_t)getu32(fsi, (fs)->fs_inopb))

/* original:
** #define itog(fs, x)    ((x) / (fs)->fs_cg_inode_num)
*/
#define itog_lcl(fsi, fs, x)	\
	((x) / gets32(fsi, (fs)->cg_inode_num))

/* original:
** dtog(fs, d) ((d) / (fs)->fs_cg_frag_num)
*/
#define dtog_lcl(fsi, fs, d)	\
	((d) / gets32(fsi, (fs)->cg_frag_num))

#define cg_inosused_lcl(fsi, cgp)	\
	((uint8_t *)((uint8_t *)(cgp) + gets32(fsi, (cgp)->cg_iusedoff)))

#define cg_blksfree_lcl(fsi, cgp) \
	((uint8_t *)((uint8_t *)(cgp) + gets32(fsi, (cgp)->cg_freeoff)))




/*
 * Structure of a fast file system handle.
 */
    typedef struct {
	FS_INFO fs_info;	/* super class */
	union {
	    ffs_sb1 *sb1;	/* super block buffer */
	    ffs_sb2 *sb2;	/* super block buffer */
	} fs;

	char *dino_buf;		/* cached disk inode */
	INUM_T dino_inum;	/* address of cached disk inode */

	DATA_BUF *itbl_buf;	/* cached inode block buffer */

	DATA_BUF *grp_buf;	/* Cached cylinder group buffer */
	FFS_GRPNUM_T grp_num;	/* number of cached cyl */

	FFS_GRPNUM_T groups_count;	/* nr of descriptor group blocks */

	unsigned int ffsbsize_f;	/* num of frags in an FFS block */
	unsigned int ffsbsize_b;	/* size of an FFS block in bytes */
    } FFS_INFO;

#ifdef __cplusplus
}
#endif
#endif				/* _FFS_H */
