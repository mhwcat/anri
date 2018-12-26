#ifndef ANRI_RESOURCE_MANAGER_H
#define ANRI_RESOURCE_MANAGER_H

#include <map>

class ResourceManager 
{
    // When inheriting this class, remember to declare map with resource for base type
    //protected:
    //    std::map<keyT, valT> resources;
    
    public:
        //virtual void remove() = 0;
        virtual void clear() = 0;
        
};

#endif