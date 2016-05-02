/*
 * Copyright (C) 2005-2013 Sourcefire, Inc. All Rights Reserved
 *
 * This file may contain proprietary rules that were created, tested and
 * certified by Sourcefire, Inc. (the "VRT Certified Rules") as well as
 * rules that were created by Sourcefire and other third parties and
 * distributed under the GNU General Public License (the "GPL Rules").  The
 * VRT Certified Rules contained in this file are the property of
 * Sourcefire, Inc. Copyright 2005 Sourcefire, Inc. All Rights Reserved.
 * The GPL Rules created by Sourcefire, Inc. are the property of
 * Sourcefire, Inc. Copyright 2002-2005 Sourcefire, Inc. All Rights
 * Reserved.  All other GPL Rules are owned and copyrighted by their
 * respective owners (please see www.snort.org/contributors for a list of
 * owners and their respective copyrights).  In order to determine what
 * rules are VRT Certified Rules or GPL Rules, please refer to the VRT
 * Certified Rules License Agreement.
 */

//#define DEBUG
#ifdef DEBUG
#define DEBUG_SO(code) code
#else
#define DEBUG_SO(code)
#endif

#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

#include "so-util.h"

/* declare detection functions */
int rule37675eval(void *p);
int rule37676eval(void *p);
static int DetectCiscoIkeBof(SFSnortPacket *sp, const uint8_t *cursor_normal, const uint8_t *end_of_buffer);

/* declare rule data structures */
/* flow:to_server; */
static FlowFlags rule_CiscoIkeBof_flow0 = 
{
   FLOW_TO_SERVER
};

static RuleOption rule_CiscoIkeBof_option0 =
{
   OPTION_TYPE_FLOWFLAGS,
   {
      &rule_CiscoIkeBof_flow0
   }
};

#ifndef CONTENT_FAST_PATTERN_ONLY
#define CONTENT_FAST_PATTERN_ONLY CONTENT_FAST_PATTERN
#endif

// content:"|84|", fast_pattern:only; 
static ContentInfo rule_CiscoIkeBof_content1 = 
{
   (uint8_t *) "|84|", /* pattern */
   0, /* depth */
   0, /* offset */
   CONTENT_FAST_PATTERN_ONLY|CONTENT_BUF_NORMALIZED, /* flags */
   NULL, /* holder for boyer/moore PTR */
   NULL, /* more holder info - byteform */
   0, /* byteform length */
   0 /* increment length*/
};

static RuleOption rule_CiscoIkeBof_option1 = 
{
   OPTION_TYPE_CONTENT,
   {
      &rule_CiscoIkeBof_content1
   }
};

// content:"|10|", offset 17, depth 1;
static ContentInfo rule37675content2 = 
{
   (uint8_t *) "|10|", /* pattern */
   1, /* depth */
   17, /* offset */
   CONTENT_BUF_NORMALIZED, /* flags */
   NULL, /* holder for boyer/moore PTR */
   NULL, /* more holder info - byteform */
   0, /* byteform length */
   0 /* increment length*/
};

static RuleOption rule37675option2 = 
{
   OPTION_TYPE_CONTENT,
   {
      &rule37675content2
   }
};

// content:"|20|", offset 17, depth 1;
static ContentInfo rule37676content2 = 
{
   (uint8_t *) "|20|", /* pattern */
   1, /* depth */
   17, /* offset */
   CONTENT_BUF_NORMALIZED, /* flags */
   NULL, /* holder for boyer/moore PTR */
   NULL, /* more holder info - byteform */
   0, /* byteform length */
   0 /* increment length*/
};

static RuleOption rule37676option2 = 
{
   OPTION_TYPE_CONTENT,
   {
      &rule37676content2
   }
};

/* references */
/* reference: cve "2016-1287"; */
static RuleReference rule_CiscoIkeBof_ref1 = 
{
   "cve", /* type */
   "2016-1287" /* value */
};

/* reference: url "tools.cisco.com/security/center/content/CiscoSecurityAdvisory/cisco-sa-20160210-asa-ike"; */
static RuleReference rule_CiscoIkeBof_ref2 = 
{
   "url", /* type */
   "tools.cisco.com/security/center/content/CiscoSecurityAdvisory/cisco-sa-20160210-asa-ike" /* value */
};

static RuleReference *rule_CiscoIkeBof_refs[] =
{
   &rule_CiscoIkeBof_ref1,
   &rule_CiscoIkeBof_ref2,
   NULL
};

/* metadata */
/* metadata:policy balanced-ips drop, policy security-ips drop; */
static RuleMetaData rule_CiscoIkeBof_policy1 = 
{
   "policy security-ips drop"
};

static RuleMetaData *rule_CiscoIkeBof_metadata[] =
{
   &rule_CiscoIkeBof_policy1,
   NULL
};

RuleOption *rule37675options[] =
{
   &rule_CiscoIkeBof_option0,
   &rule_CiscoIkeBof_option1,
   &rule37675option2,
   NULL
};

Rule rule37675 = {
   /* rule header, akin to => tcp any any -> any any */
   {
      IPPROTO_UDP, /* proto */
      "$EXTERNAL_NET", /* SRCIP     */
      "any", /* SRCPORT   */
      0, /* DIRECTION */
      "$HOME_NET", /* DSTIP     */
      "500", /* DSTPORT   */
   },
   /* metadata */
   { 
      3,  /* genid */
      37675, /* sigid */
      1, /* revision */
      "attempted-admin", /* classification */
      0,  /* hardcoded priority */
      "SERVER-OTHER Cisco ASA IKEv1 invalid fragment length heap buffer overflow attempt",     /* message */
      rule_CiscoIkeBof_refs, /* ptr to references */
      rule_CiscoIkeBof_metadata /* ptr to metadata */
   },
   rule37675options, /* ptr to rule options */
   &rule37675eval, /* uncomment to use custom detection function */
   0 /* am I initialized yet? */
};

RuleOption *rule37676options[] =
{
   &rule_CiscoIkeBof_option0,
   &rule_CiscoIkeBof_option1,
   &rule37676option2,
   NULL
};

Rule rule37676 = {
   /* rule header, akin to => tcp any any -> any any */
   {
      IPPROTO_UDP, /* proto */
      "$EXTERNAL_NET", /* SRCIP     */
      "any", /* SRCPORT   */
      0, /* DIRECTION */
      "$HOME_NET", /* DSTIP     */
      "500", /* DSTPORT   */
   },
   /* metadata */
   { 
      3,  /* genid */
      37676, /* sigid */
      1, /* revision */
      "attempted-admin", /* classification */
      0,  /* hardcoded priority */
      "SERVER-OTHER Cisco ASA IKEv2 invalid fragment length heap buffer overflow attempt",     /* message */
      rule_CiscoIkeBof_refs, /* ptr to references */
      rule_CiscoIkeBof_metadata /* ptr to metadata */
   },
   rule37676options, /* ptr to rule options */
   &rule37676eval, /* uncomment to use custom detection function */
   0 /* am I initialized yet? */
};

/* detection functions */
int rule37675eval(void *p) {
   const uint8_t *cursor_normal = 0, *end_of_buffer;
   SFSnortPacket *sp = (SFSnortPacket *) p;

   if(sp == NULL)
      return RULE_NOMATCH;

   if(sp->payload == NULL)
      return RULE_NOMATCH;

   // flow:to_server
   if(checkFlow(p, rule37675options[0]->option_u.flowFlags) <= 0)
      return RULE_NOMATCH;

   // content:"|84|", fast_pattern:only;
   // if(contentMatch(p, rule37675options[1]->option_u.content, &cursor_normal) <= 0)
   //    return RULE_NOMATCH;
  
   // content:"|10|", offset 17, depth 1;
   if(contentMatch(p, rule37675options[2]->option_u.content, &cursor_normal) <= 0)
      return RULE_NOMATCH;

   if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &cursor_normal, &end_of_buffer) <= 0)
      return RULE_NOMATCH;

   return DetectCiscoIkeBof(sp, cursor_normal, end_of_buffer);
}

int rule37676eval(void *p) {
   const uint8_t *cursor_normal = 0, *end_of_buffer;
   SFSnortPacket *sp = (SFSnortPacket *) p;

   if(sp == NULL)
      return RULE_NOMATCH;

   if(sp->payload == NULL)
      return RULE_NOMATCH;

   // flow:to_server
   if(checkFlow(p, rule37676options[0]->option_u.flowFlags) <= 0)
      return RULE_NOMATCH;

   // content:"|84|", fast_pattern:only;
   // if(contentMatch(p, rule37676options[1]->option_u.content, &cursor_normal) <= 0)
   //    return RULE_NOMATCH;
  
   // content:"|20|", offset 17, depth 1;
   if(contentMatch(p, rule37676options[2]->option_u.content, &cursor_normal) <= 0)
      return RULE_NOMATCH;

   if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &cursor_normal, &end_of_buffer) <= 0)
      return RULE_NOMATCH;

   return DetectCiscoIkeBof(sp, cursor_normal, end_of_buffer);
}

static int DetectCiscoIkeBof(SFSnortPacket *sp, const uint8_t *cursor_normal, const uint8_t *end_of_buffer) {
   int i;
   const uint8_t *next_payload_pos;
   uint8_t payload_type, next_payload_type;
   uint16_t payload_length;

   // check if we can read ISAKMP header and first payload
   if(cursor_normal + 32 > end_of_buffer)
      return RULE_NOMATCH;

   DEBUG_SO(fprintf(stderr,"ISAKMP Request:\n");)

   // move cursor to first payload type
   cursor_normal += 16;

   // read first payload type
   payload_type = *cursor_normal;

   // move to first payload
   cursor_normal += 12;

   // check up to 5 ISAKMP payloads 
   for(i = 0; i < 20; i++)
   {

      // We verify data availability above for first loop, below for subsequent loops
      next_payload_type = *cursor_normal;
      payload_length = read_big_16(cursor_normal + 2);

      DEBUG_SO(fprintf(stderr,"  payload: type 0x%02X len 0x%04X\n",payload_type,payload_length);)

      // check for vuln condition
      if((payload_type == 0x84) && (payload_length < 8))
         return RULE_MATCH;

      // payload header must be at least 4
      if(payload_length < 4)
         return RULE_NOMATCH;

      // no next payload, bail
      if(next_payload_type == 0)
         return RULE_NOMATCH;

      // calculate next payload position (payload length is at least 4)
      next_payload_pos = cursor_normal + payload_length;

      // integer overflow check
      if(next_payload_pos < cursor_normal)
         return RULE_NOMATCH;

      // check next payload
      payload_type = next_payload_type;
      cursor_normal = next_payload_pos;

      // verify we can read:
      //    next payload type (1 byte)
      //    critical          (1 byte)
      //    payload length    (2 byte BE)
      if(cursor_normal + 4 > end_of_buffer)
         return RULE_NOMATCH;
   }
   
   return RULE_NOMATCH;
}

/*
Rule *rules[] = {
    &rule37675,
    &rule37676,
    NULL
};
*/
