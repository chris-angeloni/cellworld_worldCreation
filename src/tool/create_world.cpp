#include <cell_world/paths.h>
#include <cell_world/map.h>
#include <cell_world.h>
#include <iostream>
#include <vector>
#include <params_cpp.h>

using namespace std;
using namespace cell_world;



int main(){
    string  new_world_name = "22_01";    // name of world you are creating

    // load world and create new_world to modify
    string occlusions_name = "00_00";
    auto wc = Resources::from("world_configuration").key("hexagonal").get_resource<World_configuration>();
    auto wi = Resources::from("world_implementation").key("hexagonal").key("mice").get_resource<World_implementation>();
    auto occlusions = Resources::from("cell_group").key("hexagonal").key(occlusions_name).key("occlusions").get_resource<Cell_group_builder>();
    World world1(wc, wi, occlusions);
    World world2 = world1;


    Cell_group cg1 = world1.create_cell_group();
    Cell_group cg2 = world2.create_cell_group();
    Map map1 (cg1);
    Map map2 (cg2);

    // modify world by occluding cells
    vector <vector <int>> new_occlusions {{-14,2},{-1,3},{2,-8},{16,2},{15,3}};  // [[-14, 2], [-1, 3], [2, -8], [16, 2], [15, 3]]
    for ( auto c : new_occlusions){
        world2.cells[cg2.find(Coordinates(c[0],c[1]))].occluded = true;
    }


    // create new paths
    Graph graph = world2.create_graph();
    Paths paths(graph);
    auto new_path = paths.get_astar(graph);
//    cout << new_path << endl;

    new_path.save("../../cellworld_data/paths/hexagonal." + new_world_name + ".astar");    // MAKE SURE PATHS ARE NAMED PROPERLY

     // create new occluded list
    cg2.occluded_cells().save("../../cellworld_data/cell_group/hexagonal."+ new_world_name +".occlusions");  // MAKE SURE WORLD ARE IS NAMED PROPERLY
    cout << "done....." << endl;
    cout << " New world and paths created: " << new_world_name  << endl;

    return 0;
}

/*
 * 1. Create world and paths using this file (make sure to check name)
 * 2. Upload to github (cellworld_data repo: https://github.com/germanespinosa/cellworld_data)
 * 3. Plot new world to make sure it's correct (https://colab.research.google.com/drive/1x5mYi_xgKvgpq4Y6vKxOjX0VJlNq6aLt#scrollTo=nylc_rPS1lZ_)
 * 4. create robot world and paths (make sure occlusion name correlates with world created in this file)
 * 5. create predation destinations and upload !!
 * 6. create visibility and upload  !!
 * 7. create spawn locations
 * 8. (extra) test in simulation
 */