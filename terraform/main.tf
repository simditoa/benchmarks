provider "google" {
  project = var.project_id
  region  = var.region
  zone    = var.zone
}

locals {
  suffix        = var.name_suffix != "" ? var.name_suffix : formatdate("YYYYMMDDhhmmss", timestamp())
  instance_name = "itoa-bench-${local.suffix}"
  network_tag   = "itoa-bench"
}

resource "google_compute_firewall" "ssh" {
  name    = "itoa-bench-allow-ssh-${local.suffix}"
  network = "default"

  allow {
    protocol = "tcp"
    ports    = ["22"]
  }

  source_ranges = ["0.0.0.0/0"]
  target_tags   = [local.network_tag]
}

resource "google_compute_instance" "bench" {
  name             = local.instance_name
  machine_type     = var.machine_type
  zone             = var.zone
  tags             = [local.network_tag]
  min_cpu_platform = var.min_cpu_platform != "" ? var.min_cpu_platform : null

  boot_disk {
    initialize_params {
      image = "ubuntu-os-cloud/ubuntu-2204-lts"
      size  = 50
      type  = "pd-balanced"
    }
  }

  network_interface {
    network = "default"
    access_config {}
  }

  metadata = {
    ssh-keys               = "${var.ssh_user}:${var.ssh_pubkey}"
    block-project-ssh-keys = "TRUE"
  }

  labels = {
    purpose = "ephemeral-benchmark"
  }

  scheduling {
    preemptible         = false
    automatic_restart   = true
    on_host_maintenance = "MIGRATE"
  }
}
