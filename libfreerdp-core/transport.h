/**
 * FreeRDP: A Remote Desktop Protocol Client
 * Network Transport Layer
 *
 * Copyright 2011 Vic Lee
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TRANSPORT_H
#define __TRANSPORT_H

#include "tcp.h"
#include "tls.h"

#include <time.h>
#include <freerdp/types/base.h>
#include <freerdp/utils/stream.h>

enum _TRANSPORT_STATE
{
	TRANSPORT_STATE_INITIAL,
	TRANSPORT_STATE_NEGO,
	TRANSPORT_STATE_RDP,
	TRANSPORT_STATE_TLS,
	TRANSPORT_STATE_NLA,
	TRANSPORT_STATE_FINAL
};
typedef enum _TRANSPORT_STATE TRANSPORT_STATE;

typedef struct rdp_transport rdpTransport;
typedef int (* PacketReceivedCallback) (rdpTransport * transport, STREAM * stream, void* extra);

struct rdp_transport
{
	TRANSPORT_STATE state;
	struct rdp_tcp * tcp;
	struct rdp_tls * tls;
	struct timespec ts;
	STREAM * recv_buffer;
	PacketReceivedCallback recv_callback;
	void* recv_extra;
};

rdpTransport *
transport_new(void);
void
transport_free(rdpTransport * transport);
FRDP_BOOL
transport_connect(rdpTransport * transport, const char * server, int port);
FRDP_BOOL
transport_disconnect(rdpTransport * transport);
FRDP_BOOL
transport_connect_rdp(rdpTransport * transport);
FRDP_BOOL
transport_connect_tls(rdpTransport * transport);
FRDP_BOOL
transport_connect_nla(rdpTransport * transport);
int
transport_send(rdpTransport * transport, STREAM * stream);
int
transport_check_fds(rdpTransport * transport);

#endif