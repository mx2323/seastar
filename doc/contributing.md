Contributing to Seastar
============


# Coding Standards
    void tcp_option::parse(uint8_t* beg, uint8_t* end) {
        while (beg < end) {
            auto kind = option_kind(*beg);

 * Curly brace on the same line as conditional statements. 
 * Open curly brace right after list of parameters of a function declaration. 
 * Indentation, 4 spaces.

# Sending Patches
Seastar follows a patch submission similar to Linux. Send patches to seastar-dev, with a DSO signed off message. Use git-format-patch and git send-email to send your patch.

Example:

1. creates a patch file that can be edited. -s adds a DSO signed off message.


        git format-patch -s 6623379..25a5dd5  

2. then edit the patch file generated to include comments, notes, a descriptive subject line, etc. 

3. then send an email to the google group with the patch 

        git send-email --annotate --to seastar-dev@googlegroups.com <name_of_patch.patch>

# Commit messages
Please make commit messages descriptive. You can prefix a tag for an area of the codebase the patch is addressing 

example:

    rpc: fix peer address printing during logging 

# Testing and Approval
Run test.py and ensure tests are passing (at least) as well as before the patch. 








