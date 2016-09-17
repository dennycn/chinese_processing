/**
 * @file crc32.h
 * @author Hightman Mar
 * @editor set number ; syntax on ; set autoindent ; set tabstop=4 (vim)
 * $Id: crc32.h,v 1.2 2010/01/28 16:45:47 hightman Exp $
 */

#ifndef	_SCWS_CRC32_20100128_H_
#define	_SCWS_CRC32_20100128_H_

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

unsigned int scws_crc32(const char *str);

#endif
