# nfp400_traffic_foward

A basic traffic reflecting and fowarding applicaion for the NFP 400 2x10GE network card.

This repository is based on the c_packetprocessing repository (https://github.com/open-nfpsw/c_packetprocessing) and contains the same directory structure and build scripts.

# Structure

Components of this repository are structured as follows:

- 'apps' contains the application code for the wire and reflector example.
- 'microc' contains supporting libraries.
- 'scripts' contains Makefile templates.

# Build and Run

To run the wire application example:

1. navigate to the apps/wire directory and run the makefile.
   ```
   > cd apps/wire
   > make
   ```
 
2. Call the initialization script in the init subdirectory to handle the flashing and configuration.
   ```
   > ./init/wire.sh restart wire.fw
   ```
  
To run the reflector application example:

1. navigate to the apps/wire directory and run the makefile.
   ```
   > cd apps/reflector
   > make
   ```
 
2. Call the initialization script in the init subdirectory to handle the flashing and configuration.
   ```
   > ./init/reflector.sh restart reflector.fw
   ```

# Testing

Sample captures can be found online (https://wiki.wireshark.org/SampleCaptures) (http://packetlife.net/captures/)

This is largely based on your physical setup. As an example setup, assuming a dedicated connection to each of the physical interfaces on the NFP card:

- Use tshark on the test host(s) to record traffic being passed over an interface.
  ```
  > sudo tshark -x -i eth0
  ```

- Use tcpreplay to replay traffic recored in pcap file over the interface:
  ```
  > sudo tcpreplay --intf1=eth0 sample.pcap
  ```
 
## Wire Application
- For every packet sent, the tshark instance should record one copy of the packet (the egress packet). If tshark was running on the host connected to the opposing NFP physical interface, it too should have recored the same packet.

## Reflector Application
- For every packet sent, the tshark instance on the same host should record two copies of the packet (the egress packet and the reflected packet). If tshark was running on the host connected to the opposing NFP physical interface, it should have recorded nothing.
