/*
 * CPUID
 *
 * A simple and small tool to dump/decode CPUID information.
 *
 * Copyright (c) 2010-2021, Steven Noonan <steven@uplinklabs.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef __vendor_h
#define __vendor_h

typedef enum
{
	VENDOR_UNKNOWN      = 0x0,
	VENDOR_INTEL        = 0x1,
	VENDOR_AMD          = 0x2,
	VENDOR_CYRIX        = 0x4,
	VENDOR_TRANSMETA    = 0x8,
	VENDOR_HYGON        = 0x10, /* Chinese-manufactured AMD EPYC clone. */
	VENDOR_CENTAUR      = 0x20,

	VENDOR_HV_XEN       = 0x100,
	VENDOR_HV_VMWARE    = 0x200,
	VENDOR_HV_KVM       = 0x400,
	VENDOR_HV_HYPERV    = 0x800,
	VENDOR_HV_PARALLELS = 0x1000,
	VENDOR_HV_BHYVE     = 0x2000,
	VENDOR_HV_GENERIC   = 0x4000,

	VENDOR_ANY          = (int)-1
} cpu_vendor_t;

#endif

/* vim: set ts=4 sts=4 sw=4 noet: */
