help:
	@echo "Help."

build_opensuse_leap:
	sudo docker build - < opensuse_leap > opensuse_leap.out 2>&1 &

build_opensuse_leap_dev:
	sudo docker build - < opensuse_leap_dev > opensuse_leap_dev.out 2>&1 &

build_ubuntu:
	sudo docker build - < ubuntu > ubuntu.out 2>&1 &

build_ubuntu_dev:
	sudo docker build - < ubuntu_dev > ubuntu_dev.out 2>&1 &

build_ubuntu_dev_nolinalg:
	sudo docker build - < ubuntu_dev_nolinalg \
		> ubuntu_dev_nolinalg.out 2>&1 &
