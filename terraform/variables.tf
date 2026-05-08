variable "project_id" {
  description = "GCP project ID."
  type        = string
}

variable "region" {
  description = "GCP region."
  type        = string
  default     = "us-central1"
}

variable "zone" {
  description = "GCP zone."
  type        = string
  default     = "us-central1-a"
}

variable "machine_type" {
  description = "GCE machine type."
  type        = string
  default     = "c3-standard-8"
}

variable "min_cpu_platform" {
  description = "Optional minimum CPU platform (e.g. 'Intel Ice Lake'). Leave empty to use the GCE default."
  type        = string
  default     = ""
}

variable "ssh_user" {
  description = "Linux user for SSH login."
  type        = string
  default     = "ubuntu"
}

variable "ssh_pubkey" {
  description = "SSH public key (single line, OpenSSH format)."
  type        = string
}

variable "name_suffix" {
  description = "Suffix appended to resource names to avoid collisions across runs."
  type        = string
  default     = ""
}

variable "prefix" {
  description = "Prefix applied to resource names and the network tag."
  type        = string
  default     = "benchmark"
}
