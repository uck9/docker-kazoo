: ${ACCOUNT:=test}
: ${REALM:=localhost}
: ${ADMIN_USER:=admin}
: ${ADMIN_PASS:=secret}
: ${LANGUAGE:=en-us}
: ${MEDIA_PATH:=/opt/kazoo/media/prompts/en/us}
: ${KAPPS_PATH:=/var/www/html/monster-ui/apps}
: ${CROSSBAR_URI:=http://$HOST:8000/v2}


function test {
	sup kapps_controller list_apps
}

function create-master-account {
	sup crossbar_maintenance create_account $ACCOUNT $REALM $ADMIN_USER $ADMIN_PASS
}

function get-master-account {
	sup crossbar_maintenance find_account_by_name $ACCOUNT
}

function load-media {
	sup kazoo_media_maintenance import_prompts $MEDIA_PATH $LANGUAGE
}

function init-apps {
	sup crossbar_maintenance init_apps $KAPPS_PATH $CROSSBAR_URI
}

function list-apps {
	sup crossbar_maintenance apps
}

function add-fs-node {
	echo "adding node: freeswitch@$FREESWITCH_HOST"
	sup ecallmgr_maintenance add_fs_node freeswitch@$FREESWITCH_HOST
}

function list-fs-nodes {
	sup ecallmgr_maintenance list_fs_nodes
}

function allow-sbc {
	echo "adding label: $KAMAILIO_HOST ip: $KAMAILIO_IP"
	sup ecallmgr_maintenance allow_sbc $KAMAILIO_HOST $KAMAILIO_IP
}

function sbc-acls {
	sup ecallmgr_maintenance sbc_acls
}

function all {
	create-master-account
	load-media
	init-apps
	add-fs-node
	allow-sbc
}

function check {
	get-master-account
	list-apps
	list-fs-nodes
	sbc-acls
}

if [[ $1 ]]; then
    "$@"
else
    echo "usage: $(basename $0) {sup|test|create-master-acccount|get-master-account|load-media|init-apps|list-apps|add-fs-node|list-fs-nodes|allow-sbc|sbc-acls|all}"
    exit 1
fi
