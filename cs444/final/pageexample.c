int vm_fault (
        vm_map_t map,
        vm_offset_t addr,
        vm_prot_t type)
{
    RetryFault:
        lookup address in map returning object/offset/prot;
        first_object = object;
        first_page = NULL;

        //Traverses list of vm_objects until find item with page, or reaches final and requests page from that object
        for(;;){
            page = lookup page at object/offset;

            //The page is found!
            if(page found) {
                //If the page is busy, another process could be using it
                //So we goto the retryfault until its not busy
                if(page busy)
                    block and goto RetryFault;
                //Otherwise, get the page
                remove from paging queues;
                mark page as busy;
                break;
            }

            /*
             *Omitted some non-relavant code 
             */

            //Makes sure the first page is remembered
            if(object == first_object)
                first_page = page;
            next_object = next object;
            
            //Makes the first object handle the fault if the right page isn't found
            if(no next object) {
                if(object != first_object) {
                    object = first_object;
                    page = first_page;
                }
                first_page = NULL;
                zero fill page;
                break
            }
            object = next_object
        }

        //The found or allocated page
        orig_page = page;
        
        /*
         *Ommited some non-relavant code
         */

        //Now the page can safely be made writeable
        if(prot & WRITE)
            mark page not copy-on-write;
        enter mapping for page;
        enter read-only mapping for clustered pages;

        //Now processes waiting on this page can use it
        activate and unbusy page;
        if(first_page != NULL)
            unbusy page;
}
