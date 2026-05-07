output "vm_name" {
  value = google_compute_instance.bench.name
}

output "vm_zone" {
  value = google_compute_instance.bench.zone
}

output "vm_external_ip" {
  value = google_compute_instance.bench.network_interface[0].access_config[0].nat_ip
}

output "ssh_user" {
  value = var.ssh_user
}
