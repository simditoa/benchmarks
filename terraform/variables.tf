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
  default     = "n2-standard-96"
}

variable "ssh_user" {
  description = "Linux user for SSH login."
  type        = string
  default     = "bench"
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
