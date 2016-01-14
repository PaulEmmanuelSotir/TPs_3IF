/*********************************************************************************
 Rectangle
 ---------
 *********************************************************************************/

#ifndef POLYGONE_H
#define POLYGONE_H

#include <ostream>

#include "Forme.h"
#include "Utils.h"

//! \namespace TP4
//! espace de nommage regroupant le code crÈe pour le TP4 de C++
namespace TP4
{
    struct Polygone : Forme
    {
        Polygone() = default;
        Polygone(std::string name);
        virtual ~Polygone() = default;
        
        void Move(double dx, double dy) override;
        bool IsContained(double x, double y) override;
        virtual bool IsConvex();
        
        void SerializeTo(const std::ostream& output_stream) override;
        void DeserializeFrom(const std::ostream& output_stream) override;
        
        std::string name;
        std::vector<Point> tab;
        
    };
}

#endif // POLYGONE_H
