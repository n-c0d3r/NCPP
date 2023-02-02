#pragma once

namespace ncpp { 
    
    /**
     *  Implementing parallelism and concurrency functionalities.  
     */
    namespace pac {} 
}

#include <ncpp/prerequisites.hpp>

#include <ncpp/utilities/.hpp>
#include <ncpp/containers/.hpp>

#include <ncpp/pac/spinlock.hpp>
#include <ncpp/pac/semaphore.hpp>
#include <ncpp/pac/fiber.hpp>
	
#ifdef NCPP_WINDOWS_PLATFORM
#include <ncpp/pac/win_fiber.hpp>
#endif