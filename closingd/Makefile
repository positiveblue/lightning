#! /usr/bin/make

# Designed to be run one level up
closingd-wrongdir:
	$(MAKE) -C ../.. closingd-all

default: closingd-all

closingd-all: lightningd/lightning_closingd

# closingd needs these:
LIGHTNINGD_CLOSING_HEADERS_GEN :=			\
	closingd/gen_closing_wire.h

LIGHTNINGD_CLOSING_HEADERS_NOGEN :=

LIGHTNINGD_CLOSING_HEADERS := $(LIGHTNINGD_CLOSING_HEADERS_GEN) $(LIGHTNINGD_CLOSING_HEADERS_NOGEN)

LIGHTNINGD_CLOSING_SRC := closingd/closingd.c	\
	$(LIGHTNINGD_CLOSING_HEADERS:.h=.c)
LIGHTNINGD_CLOSING_OBJS := $(LIGHTNINGD_CLOSING_SRC:.c=.o)

# Make sure these depend on everything.
ALL_OBJS += $(LIGHTNINGD_CLOSING_OBJS)
ALL_PROGRAMS += lightningd/lightning_closingd
ALL_GEN_HEADERS += $(LIGHTNINGD_CLOSING_HEADERS_GEN)

# Control daemon uses this:
LIGHTNINGD_CLOSING_CONTROL_HEADERS := $(LIGHTNINGD_CLOSING_HEADERS)
LIGHTNINGD_CLOSING_CONTROL_SRC := $(LIGHTNINGD_CLOSING_HEADERS:.h=.c)
LIGHTNINGD_CLOSING_CONTROL_OBJS := $(LIGHTNINGD_CLOSING_CONTROL_SRC:.c=.o)

LIGHTNINGD_CLOSING_GEN_SRC := $(filter closingd/gen_%, $(LIGHTNINGD_CLOSING_SRC) $(LIGHTNINGD_CLOSING_CONTROL_SRC))

LIGHTNINGD_CLOSING_SRC_NOGEN := $(filter-out closingd/gen_%, $(LIGHTNINGD_CLOSING_SRC))

# Add to headers which any object might need.
LIGHTNINGD_HEADERS_GEN += $(LIGHTNINGD_CLOSING_HEADERS_GEN)
LIGHTNINGD_HEADERS_NOGEN += $(LIGHTNINGD_CLOSING_HEADERS_NOGEN)

$(LIGHTNINGD_CLOSING_OBJS): $(LIGHTNINGD_HEADERS)

# Common source we use.
CLOSINGD_COMMON_OBJS :=				\
	common/amount.o				\
	common/base32.o				\
	common/bigsize.o			\
	common/bip32.o				\
	common/channel_id.o			\
	common/close_tx.o			\
	common/crypto_state.o			\
	common/crypto_sync.o			\
	common/cryptomsg.o			\
	common/daemon.o				\
	common/daemon_conn.o			\
	common/dev_disconnect.o			\
	common/derive_basepoints.o		\
	common/gen_peer_status_wire.o		\
	common/gen_status_wire.o		\
	common/gossip_rcvd_filter.o		\
	common/gossip_store.o			\
	common/htlc_wire.o			\
	common/key_derive.o			\
	common/memleak.o			\
	common/msg_queue.o			\
	common/node_id.o			\
	common/onionreply.o			\
	common/peer_billboard.o			\
	common/peer_failed.o			\
	common/per_peer_state.o			\
	common/permute_tx.o			\
	common/pseudorand.o			\
	common/read_peer_msg.o			\
	common/setup.o				\
	common/socket_close.o			\
	common/status.o				\
	common/status_wire.o			\
	common/subdaemon.o			\
	common/type_to_string.o			\
	common/utils.o				\
	common/utxo.o				\
	common/version.o			\
	common/wire_error.o			\
	common/wireaddr.o			\
	gossipd/gen_gossip_peerd_wire.o		\
	hsmd/gen_hsm_wire.o

closingd/gen_closing_wire.h: $(WIRE_GEN) closingd/closing_wire.csv
	$(WIRE_GEN) --page header $@ closing_wire_type < closingd/closing_wire.csv > $@

closingd/gen_closing_wire.c: $(WIRE_GEN) closingd/closing_wire.csv
	$(WIRE_GEN) --page impl ${@:.c=.h} closing_wire_type < closingd/closing_wire.csv > $@

LIGHTNINGD_CLOSING_OBJS := $(LIGHTNINGD_CLOSING_SRC:.c=.o) $(LIGHTNINGD_CLOSING_GEN_SRC:.c=.o)

lightningd/lightning_closingd: $(LIGHTNINGD_CLOSING_OBJS) $(WIRE_ONION_OBJS) $(CLOSINGD_COMMON_OBJS) $(WIRE_OBJS) $(BITCOIN_OBJS) $(LIGHTNINGD_HSM_CLIENT_OBJS)

check-source: $(LIGHTNINGD_CLOSING_SRC_NOGEN:%=check-src-include-order/%)
check-source-bolt: $(LIGHTNINGD_CLOSING_SRC:%=bolt-check/%) $(LIGHTNINGD_CLOSING_HEADERS:%=bolt-check/%)

check-whitespace: $(LIGHTNINGD_CLOSING_SRC_NOGEN:%=check-whitespace/%) $(LIGHTNINGD_CLOSING_HEADERS_NOGEN:%=check-whitespace/%)

clean: closingd-clean

closingd-clean:
	$(RM) $(LIGHTNINGD_CLOSING_OBJS) closingd/gen_*

-include closingd/test/Makefile
