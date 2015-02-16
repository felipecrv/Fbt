/**
 * @file fbt_trampoline.c
 * Implementation of thread local trampolines.
 *
 * Copyright (c) 2011 ETH Zurich
 * Copyright (c) 2015 Felipe O. Carvalho
 * @author Mathias Payer <mathias.payer@nebelwelt.net>
 * @author Felipe O. Carvalho <felipekde@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of thce GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#include "../fbt_trampoline.h"
#include "../fbt_datatypes.h"

void fbt_initialize_trampolines(struct thread_local_data *tld) {
  //initialize_unmanaged_code_trampoline(tld);
  //initialize_ret2app_trampoline(tld);
  //initialize_ijump_trampoline(tld);
  //initialize_icall_trampoline(tld);
  //initialize_ret_trampolines(tld);
  //initialize_sysenter_trampoline(tld);
}
