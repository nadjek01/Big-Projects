/*
 *  Program to explore large memory allocations.
 *
 *  Mark A. Sheldon, Tufts University, Fall 2016
 *
 *  Interesting facts:
 *
 *       - There is a logical limit on the heap allocations you can
 *         make.  If you use "new" and there not sufficient heap
 *         storage available, C++ throws a bad_alloc exception.
 *       - The heap manager is willing to make promises the OS can't
 *         keep:  You can allocate more heap memory than is physicaly
 *         available.  
 *       - Newly allocated memory is, in Linux, mapped to
 *         the 0 page.
 *       - If you modify the page, then the Linux VM has to allocate
 *         an address area for "copy on write."
 *       - If no physical resources are available, your program is
 *         killed.
 *
 *  Example:
 *
 *     vm-hw06{msheldon}1016: ./exceedmem 1000000 1000000
 *     terminate called after throwing an instance of 'std::bad_alloc'
 *       what():  std::bad_alloc
 *     Aborted
 *     vm-hw06{msheldon}1017: ./exceedmem 1000000 10000
 *     Killed
 *     vm-hw06{msheldon}1017: 
 */
#include <iostream>
#include <cstdlib>
#include <cstdint>

using namespace std;

void usage_abort(string prog_name)
{
        cerr << "Usage:  "
             << prog_name
             << " number_of_allocations allocation_size" << endl
             << "     where allocation_size is in KB"
             << endl;
        exit(1);
}

void get_args(int argc, char *argv[],
              uint64_t &num_allocations,
              uint64_t &allocation_size)
{
        if (argc != 3)
                usage_abort(argv[0]);
        num_allocations = stol(argv[1]);
        allocation_size = stol(argv[2]) * 1024;
}

int main(int argc, char *argv[])
{
        uint64_t  num_allocations, allocation_size;
        char     *bytes_p;

        get_args(argc, argv, num_allocations, allocation_size);

	for (uint64_t i = 0; i < num_allocations; ++i)
		bytes_p = new char[allocation_size];

	cout << "Allocation complete" << endl;
	cout << "Modifying one byte of most recently allocated block" << endl;
	cout << flush;

        bytes_p[0] = 'x';

        cout << "All done!" << endl;

        return 0;
}
