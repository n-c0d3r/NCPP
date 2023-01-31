#pragma once

#include <ncpp/utilities.hpp>

#include <ncpp/tmp_helper/tmp_helper.hpp>
#include <ncpp/containers/containers.hpp>
#include <ncpp/dod/dod.hpp>



namespace ncpp {

    namespace ecs {

        template<template<typename data_type> class allocator_t = std::allocator>
        class NCPP_DEFAULT_ALIGN world_it {

        private:
            world_it();
            ~world_it();

        };

    }

}