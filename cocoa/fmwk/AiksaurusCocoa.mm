/* -*- mode: C++; tab-width: 4; c-basic-offset: 4; -*- */

/* Aiksaurus / Cocoa front-end
 * Copyright (C) 2003 Francis James Franklin <fjf@alinameridon.com>
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 */

#include "AiksaurusCocoa.h"
#include "Aiksaurus.h"

@implementation AiksaurusCocoa

- (id)init
{
	try
		{
			Aiksaurus * aik = new Aiksaurus;
			m_aiksaurus = reinterpret_cast<void *>(aik);
		}
	catch (...)
		{
			m_aiksaurus = 0;
		}
	return self;
}

- (void)dealloc
{
	if (m_aiksaurus)
		{
			Aiksaurus * aik = reinterpret_cast<Aiksaurus *>(m_aiksaurus);
			delete aik;
			m_aiksaurus = 0;
		}
}

@end
