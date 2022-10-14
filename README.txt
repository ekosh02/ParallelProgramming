dnf linux:

    sudo dnf upgrade

    sudo dnf install openmpi
    sudo dnf install openmpi-devel

    sudo dnf provides */mpicc
    sudo ln -s /usr/lib64/openmpi/bin/mpicc /usr/bin/mpicc

    which mpicc

macos:

    brew install open-mpi

build & run:

    gedit filename.c
    mpicc filename.c -o filename

    mpirun -n 4 filename
    ./filename
