/*
 * Copyright (c) 2012 Nicira, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OFPROTO_DPIF_IPFIX_H
#define OFPROTO_DPIF_IPFIX_H 1

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "lib/odp-util.h"

struct flow;
struct ofpbuf;
struct ofproto_ipfix_bridge_exporter_options;
struct ofproto_ipfix_flow_exporter_options;
struct flow_tnl;
struct ofport;

struct dpif_ipfix *dpif_ipfix_create(void);
struct dpif_ipfix *dpif_ipfix_ref(const struct dpif_ipfix *);
void dpif_ipfix_unref(struct dpif_ipfix *);

void dpif_ipfix_add_tunnel_port(struct dpif_ipfix *, struct ofport *, odp_port_t);
void dpif_ipfix_del_tunnel_port(struct dpif_ipfix *, odp_port_t);

uint32_t dpif_ipfix_get_bridge_exporter_probability(const struct dpif_ipfix *);
bool dpif_ipfix_get_bridge_exporter_tunnel_sampling(const struct dpif_ipfix *);
bool dpif_ipfix_get_bridge_exporter_input_sampling(const struct dpif_ipfix *);
bool dpif_ipfix_get_bridge_exporter_output_sampling(const struct dpif_ipfix *);
bool dpif_ipfix_get_tunnel_port(const struct dpif_ipfix *, odp_port_t);
void dpif_ipfix_set_options(
    struct dpif_ipfix *,
    const struct ofproto_ipfix_bridge_exporter_options *,
    const struct ofproto_ipfix_flow_exporter_options *, size_t);

void dpif_ipfix_bridge_sample(struct dpif_ipfix *, const struct ofpbuf *,
                              const struct flow *,
                              odp_port_t, odp_port_t, const struct flow_tnl *);
void dpif_ipfix_flow_sample(struct dpif_ipfix *, const struct ofpbuf *,
                            const struct flow *, uint32_t, uint16_t, uint32_t,
                            uint32_t);

void dpif_ipfix_run(struct dpif_ipfix *);
void dpif_ipfix_wait(struct dpif_ipfix *);

#endif /* ofproto/ofproto-dpif-ipfix.h */
