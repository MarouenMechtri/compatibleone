
#ifndef	_occi_builder_h
#define	_occi_builder_h

#include "cords.h"

public struct occi_category * occi_cords_import_builder(char *a,char * b);
public struct occi_category * occi_cords_agreement_builder(char *a,char * b);
public struct occi_category * occi_cords_schedule_builder(char *a,char * b);
public struct occi_category * occi_cords_interface_builder(char *a,char * b);
public struct occi_category * occi_cords_session_builder(char *a,char * b);
public struct occi_category * occi_cords_consumer_builder(char *a,char * b);
public struct occi_category * occi_cords_connection_builder(char *a,char * b);
public struct occi_category * occi_cords_stream_builder(char *a,char * b);
public struct occi_category * occi_cords_probe_builder(char *a,char * b);
public struct occi_category * occi_cords_metric_builder(char *a,char * b);
public struct occi_category * occi_cords_alert_builder(char *a,char * b);
public struct occi_category * occi_cords_quota_builder(char *a,char * b);
public struct occi_category * occi_cords_port_builder(char *a,char * b);
public struct occi_category * occi_cords_firewall_builder(char *a,char * b);

public struct occi_category * occi_cords_application_builder(char *a,char * b);
public struct occi_category * occi_cords_instruction_builder(char *a,char * b);
public struct occi_category * occi_cords_instance_builder(char *a,char * b);
public struct occi_category * occi_cords_value_builder(char *a,char * b);
public struct occi_category * occi_cords_vm_builder(char *a,char * b);

public struct occi_category * occi_cords_metadata_builder(char *a,char * b);
public struct occi_category * occi_cords_file_builder(char *a,char * b);
public struct occi_category * occi_cords_script_builder(char *a,char * b);

public struct occi_category * occi_cords_operator_builder(char *a,char * b);
public struct occi_category * occi_cords_optimise_builder(char *a,char * b);
public struct occi_category * occi_cords_parameter_builder(char *a,char * b);
public struct occi_category * occi_cords_algorithm_builder(char *a,char * b);
public struct occi_category * occi_cords_placement_builder(char *a,char * b);
public struct occi_category * occi_cords_monitor_builder(char *a,char * b);
public struct occi_category * occi_cords_event_builder(char *a,char * b);
public struct occi_category * occi_cords_report_builder(char *a,char * b);
public struct occi_category * occi_cords_account_builder(char *a,char * b);
public struct occi_category * occi_cords_action_builder(char *a,char * b);
public struct occi_category * occi_cords_node_builder(char *a,char * b);
public struct occi_category * occi_cords_authorization_builder(char *a,char * b);
public struct occi_category * occi_cords_provider_builder(char *a,char * b);
public struct occi_category * occi_cords_compute_builder(char *a,char * b);
public struct occi_category * occi_cords_configuration_builder(char *a,char * b);
public struct occi_category * occi_cords_constraint_builder(char *a,char * b);
public struct occi_category * occi_cords_image_builder(char *a,char * b);
public struct occi_category * occi_cords_infrastructure_builder(char *a,char * b);
public struct occi_category * occi_cords_service_builder(char *a,char * b);
public struct occi_category * occi_cords_invoice_builder(char *a,char * b);
public struct occi_category * occi_cords_contract_builder(char *a,char * b);
public struct occi_category * occi_cords_network_builder(char *a,char * b);
public struct occi_category * occi_cords_package_builder(char *a,char * b);
public struct occi_category * occi_cords_profile_builder(char *a,char * b);
public struct occi_category * occi_cords_plan_builder(char *a,char * b);
public struct occi_category * occi_cords_price_builder(char *a,char * b);
public struct occi_category * occi_cords_manifest_builder(char *a,char * b);
public struct occi_category * occi_cords_requirement_builder(char *a,char * b);
public struct occi_category * occi_cords_security_builder(char *a,char * b);
public struct occi_category * occi_cords_storage_builder(char *a,char * b);
public struct occi_category * occi_cords_system_builder(char *a,char * b);
public struct occi_category * occi_cords_transaction_builder(char *a,char * b);
public struct occi_category * occi_cords_tarif_builder(char *a,char * b);
public struct occi_category * occi_cords_user_builder(char *a,char * b);
public struct occi_category * occi_cords_xlink_builder(char *a,char * b);

public struct occi_category * occi_publication_builder(char *a,char * b);
public struct occi_category * occi_cords_enquiry_builder(char *a,char * b);
public struct occi_category * occi_cords_agency_builder(char *a,char * b);

public struct occi_category * occi_openstack_builder(char *a,char * b);
public struct occi_category * occi_cords_osconfig_builder(char *a,char * b);
public struct occi_category * occi_opennebula_builder(char *a,char * b);
public struct occi_category * occi_cords_onconfig_builder(char *a,char * b);

public struct occi_category * occi_windowsazure_builder(char *a,char * b);
public struct occi_category * occi_cords_azconfig_builder(char *a,char * b);

public struct occi_category * occi_cords_ipaddress_builder(char *a,char * b);
public struct occi_category * occi_cords_domain_builder(char *a,char * b);
public struct occi_category * occi_cords_iprange_builder(char *a,char * b);


const static struct {
	const char *name;
	public struct occi_category * (*func)(char *a,char * b);
} occiCategoryBuilder_map[]={
	{ "application", occi_cords_application_builder },
	{ "instruction", occi_cords_instruction_builder },
	{ "instance", occi_cords_instance_builder },
	{ "value", occi_cords_value_builder },
	{ "vm", occi_cords_vm_builder },
	{ "schedule", occi_cords_schedule_builder },
	{ "metadata", occi_cords_metadata_builder },
	{ "file", occi_cords_file_builder },
	{ "script", occi_cords_script_builder },
	{ "operator", occi_cords_operator_builder },
	{ "optimise", occi_cords_optimise_builder },
	{ "parameter", occi_cords_parameter_builder },
	{ "algorithm", occi_cords_algorithm_builder },
	{ "placement", occi_cords_placement_builder },
	{ "monitor", occi_cords_monitor_builder },
	{ "event", occi_cords_event_builder },
	{ "report", occi_cords_report_builder },
	{ "account", occi_cords_account_builder },
	{ "action", occi_cords_action_builder },
	{ "node", occi_cords_node_builder },
	{ "authorization", occi_cords_authorization_builder },
	{ "provider", occi_cords_provider_builder },
	{ "compute", occi_cords_compute_builder },
	{ "configuration", occi_cords_configuration_builder },
	{ "constraint", occi_cords_constraint_builder },
	{ "image", occi_cords_image_builder },
	{ "infrastructure", occi_cords_infrastructure_builder },
	{ "service", occi_cords_service_builder },
	{ "invoice", occi_cords_invoice_builder },
	{ "contract", occi_cords_contract_builder },
	{ "network", occi_cords_network_builder },
	{ "package", occi_cords_package_builder },
	{ "profile", occi_cords_profile_builder },
	{ "plan", occi_cords_plan_builder },
	{ "price", occi_cords_price_builder },
	{ "manifest", occi_cords_manifest_builder },
	{ "requirement", occi_cords_requirement_builder },
	{ "security", occi_cords_security_builder },
	{ "storage", occi_cords_storage_builder },
	{ "system", occi_cords_system_builder },
	{ "transaction", occi_cords_transaction_builder },
	{ "tarif", occi_cords_tarif_builder },
	{ "user", occi_cords_user_builder },
	{ "xlink", occi_cords_xlink_builder },
	{ "publication", occi_publication_builder },
	{ "enquiry", occi_cords_enquiry_builder },
	{ "agency", occi_cords_agency_builder },
	{ "openstack", occi_openstack_builder },
	{ "osconfig", occi_cords_osconfig_builder },
	{ "opennebula", occi_opennebula_builder },
	{ "onconfig", occi_cords_onconfig_builder },
	{ "windowsazure", occi_windowsazure_builder },
	{ "azconfig", occi_cords_azconfig_builder },
	{ "ipaddress", occi_cords_ipaddress_builder },
	{ "domain", occi_cords_domain_builder },
	{ "iprange", occi_cords_iprange_builder },
};
#endif
