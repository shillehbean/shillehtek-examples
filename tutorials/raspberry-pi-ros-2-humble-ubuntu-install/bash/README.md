# Bash examples

- [`add_ros_key.sh`](./add_ros_key.sh) — Download the ROS apt repository GPG key and save it to the system keyrings so apt can verify ROS packages.
- [`add_ros_repo.sh`](./add_ros_repo.sh) — Add the ROS 2 Humble apt repository to the system's sources.list so packages can be installed from packages.ros.org.
- [`install_ros_desktop.sh`](./install_ros_desktop.sh) — Install the prebuilt ROS 2 Humble desktop package (full desktop install with GUI tools and demos).
- [`install_ros_base.sh`](./install_ros_base.sh) — Install the ROS 2 Humble ros-base package (core ROS 2 libraries and tools without desktop GUI components).
- [`source_ros_setup.sh`](./source_ros_setup.sh) — Source the ROS 2 Humble setup script in the current shell to set ROS environment variables for this session.
- [`persist_ros_setup.sh`](./persist_ros_setup.sh) — Append the ROS 2 Humble setup script to ~/.bashrc so the ROS environment is loaded on each new shell, then source the updated bashrc.
- [`run_talker.sh`](./run_talker.sh) — Run the ROS 2 demo C++ talker node to publish sample messages on a topic for testing.
- [`run_listener.sh`](./run_listener.sh) — Run the ROS 2 demo C++ listener node to subscribe to the sample topic and print received messages.
- [`install_colcon.sh`](./install_colcon.sh) — Install python3 colcon common extensions, used for building ROS 2 packages from source.
- [`setup_rosdep.sh`](./setup_rosdep.sh) — Install and initialize rosdep, then update its database so system dependencies for ROS packages can be installed automatically.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/raspberry-pi-ros-2-humble-ubuntu-install)  
Parts: [shop at shillehtek.com](https://shillehtek.com)
