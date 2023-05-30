#ifndef APPLICATION_RETAILER_BASE_HPP
#define APPLICATION_RETAILER_BASE_HPP

#include "../application.hpp"

const string dataPath = "data/retailer";
const string r_table_path = "/R.tbl";

void Application::init_relations() {
    clear_relations();

#if defined(RELATION_R_STATIC)
    relations.push_back(std::unique_ptr<IRelation>(
            new EventDispatchableRelation<R_entry>(
                "R", dataPath + r_table_path, ',', true,
                [](dbtoaster::data_t& data) {
                    return [&](R_entry& t) {
                        data.on_insert_R(t);
                    };
                }
        )));
#elif defined(RELATION_R_DYNAMIC) && defined(BATCH_SIZE)
    typedef const std::vector<DELTA_R_entry>::iterator CIteratorR;
        relations.push_back(std::unique_ptr<IRelation>(
            new BatchDispatchableRelation<DELTA_R_entry>(
                "R", dataPath + r_table_path, ',', false,
                [](dbtoaster::data_t& data) {
                    return [&](CIteratorR& begin, CIteratorR& end) {
                        data.on_batch_update_R(begin, end);
                    };
                }
        )));
#elif defined(RELATION_R_DYNAMIC)
    relations.push_back(std::unique_ptr<IRelation>(
            new EventDispatchableRelation<R_entry>(
                "R", dataPath + r_table_path, ',', false,
                [](dbtoaster::data_t& data) {
                    return [&](R_entry& t) {
                        data.on_insert_R(t);
                    };
                }
        )));
#endif
}

#endif /* APPLICATION_RETAILER_BASE_HPP */