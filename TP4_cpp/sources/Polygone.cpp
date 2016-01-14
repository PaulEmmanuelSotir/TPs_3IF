//
//  Polygone.cpp
//  
//
//  Created by Victoire Chapelle on 14/01/2016.
//
//

#include "Polygone.h"
#include <math.h>

TP4::Polygone::Polygone(std::string name)
{
    this->name = name;
    std::vector <Point> tab;
}

void TP4::Polygone::Move(double dx, double dy)
{
    for(std::size_t i=0;i<tab.size();++i)
    {
        tab[i].first += dx;
        tab[i].second += dy;
    }
}

bool TP4::Polygone::IsContained(double x, double y)
{
    bool is_contained = false;
    double sum = 0;
    
    for (std::size_t i=0;i<tab.size()-1;++i) //Calcul de la somme des cosinus que font les angles entre les sommets consécutifs et le point
    {
        double length_1 = sqrt((tab[i].first - x)*(tab[i].first - x)+(tab[i].second - y)*(tab[i].second - y));
        double length_2 = sqrt((tab[i].first - tab[i+1].first)*(tab[i].first - tab[i+1].first)+(tab[i].second - tab[i+1].second)*(tab[i].second - tab[i+1].second));
        double length_3 = sqrt((tab[i+1].first - x)*(tab[i+1].first - x)+(tab[i+1].second - y)*(tab[i+1].second - y));
        
        double cos = (length_2*length_2)/((length_1*length_1)+(length_3*length_3)-2*length_3*length_1);
                               
        sum += cos;
    }
    
    double length_1 = sqrt((tab[tab.size()-1].first - x)*(tab[tab.size()-1].first - x)+(tab[tab.size()-1].second - y)*(tab[tab.size()-1].second - y));
    double length_2 = sqrt((tab[tab.size()-1].first - tab[0].first)*(tab[tab.size()-1].first - tab[0].first)+(tab[tab.size()-1].second - tab[0].second)*(tab[tab.size()-1].second - tab[0].second));
    double length_3 = sqrt((tab[0].first - x)*(tab[0].first - x)+(tab[0].second - y)*(tab[0].second - y));
    
    double cos = (length_2*length_2)/((length_1*length_1)+(length_3*length_3)-2*length_3*length_1);
    
    sum += cos;
    
    
    if (sum == 1) //Si la somme est 1 le point est à l'intérieur (somme des angles = 360°)
    {
        is_contained = true;
    }
                               
    return is_contained;
    
}

bool TP4::Polygone::IsConvex()
{
    bool convex = true;
    return convex;
}

void TP4::Polygone::SerializeTo(const std::ostream& output_stream)
{
    // TODO: generate JSON
}

void TP4::Polygone::DeserializeFrom(const std::ostream& output_stream)
{
    // TODO: parse JSON
}
