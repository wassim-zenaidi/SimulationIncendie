////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <list>
#include<algorithm>
#include <time.h>
#include "Analyst.h"
#include "FireSimulator.h"

FireSimulator::FireSimulator(const Image& img,int i, int j)
{
    
    copy_of_height=img.height();
    copy_of_width=img.width();
    Copy_of_Two_Dimensional_Table=new Color*[copy_of_height];
    for(int i=0;i<copy_of_height;i++){
        Copy_of_Two_Dimensional_Table[i]=new Color[copy_of_width];
    }        
    for (int j=0;j<copy_of_height;j++){
        for(int k=0;k<copy_of_width;k++){
            Copy_of_Two_Dimensional_Table[j][k]=img.getPixel(j+1,k+1);
        }
    }
    timeCounter=0;

    ///On récupère l'ensemble des indexes des pixels de la zone 
    ///où se trouve le pixels de coordonnées (i,j)
    ///grâce à la méthode zoneOfPixel de la classe Analyst.

    Analyst analysis(img);
    std::set<int> s=analysis.zoneOfPixel(i,j);
    int h=rand()%(s.size()-1);
    DrillSize=s.size();

///Pour chaque indexe de pixel de l'image, si il est présent dans 
    ///l'ensemble qui stocke les indexe de la zone
    ///alors on l'ajoute dans le tableau représentant les pixels verts(pixels de forêt) car au temps 0 
    ///le feu n'a pas débuté la forêt est encore présente partout dans la zone.

    int q=img.size();
    int r=0;
    while(r<q)
    {
        if(s.find(r)!=s.end())
        {
            vert.push_back(r);
        }
        r++;
    }
    beginning_of_fire=vert[h];
    //beginning_of_fire=img.toIndex(i,j);

    /*auto it=vert.begin();
    while(it!=vert.end()){
        std::cout<< (*it) << std::endl;
        it++;}*/
        //std::cout<< beginning_of_fire;
}

FireSimulator::~FireSimulator()
{
    for(int i=0;i<copy_of_height;i++)
    {
        delete[] Copy_of_Two_Dimensional_Table[i];
    }

    delete[] Copy_of_Two_Dimensional_Table;
}

void FireSimulator::TimeScrolling()
{

    Image need(copy_of_width,copy_of_height);
    int y=vert.size();
    ///Nous avons ajouté des phrases affiché sur le terminal 
    ///afin de pouvoir s'y retrouver quant à l'avancée du feu et des cendres.
    std::cout<< "Temps debut :  "<< timeCounter << " Temps fin : " << timeCounter+1 << std::endl;
    int d=noir.size();
    std::vector<int> temporary;
    anteriority.push_back(temporary);
    if(y!=0)
    {
       
    
        if (timeCounter==0) 
        {
            ///Si le temps est à 0, on déplace l'indexe du pixel de départ du feu dans le tableau 
            ///m_red des pixel rouge (pixels en feu) et également dans 
            ///le premier tableau du tableau m_priority. Sans oublier de l'enlever du tableau m_green.
            rouge.push_back(beginning_of_fire);
            anteriority[0].push_back(beginning_of_fire);
            //rouge.push_back(0);
            auto it=vert.begin();
            while((*it)!=beginning_of_fire){it++;}
            vert.erase(it);
        }else 
        {
            int z=rouge.size();
            int w = vert.size();
            /*std::cout << "liste vert" <<std::endl;
            auto it21=vert.begin();
            while(it21!=vert.end())
            {
                std::cout<<(*it21)<<std::endl;
                it21++;
            }*/
            for (int i = 0; i < z; i++)
            {
                std::pair<int,int> p=need.toCoordinate(rouge[i]);
                for (int j = 0; j < w ; j++)
                {
                    std::pair<int,int> q=need.toCoordinate(vert[j]);
                    if ((need.areConsecutivePixels(p.first,p.second,q.first,q.second))&&(std::find(temporary.begin(),temporary.end(),vert[j]))==temporary.end())
                    {
                        temporary.push_back(vert[j]);
                        std::cout<< "vert[j]" << vert[j]<<" a la position "<< j<< std::endl;
                    }

                }
            }
        
            /* auto it2=temporary.begin();
            while(it2!=temporary.end()){
                std::cout<<(*it2)<<std::endl;
                it2++;
            }*/
            int o=temporary.size();
            if (o>1)
            {
                
                int g=0;
                int h=rand()%(o-1);
                std::cout<<"nb pixel to color " << h+1 <<"/"<<o<< std::endl;
                while (g<=h)
                {
                    o=temporary.size();
                    int r=rand()%(o-1);
                    int e=temporary[r];
                    //std::cout <<e<<std::endl;
                    rouge.push_back(e);
                    anteriority[timeCounter].push_back(e);
                    auto it=vert.begin();
                    while((*it)!=e){it++;}
                    vert.erase(it);
                    auto it2=temporary.begin();
                    while((*it2)!=e){it2++;}
                    temporary.erase(it2);
                    g++;
                }  
            }else 
            {
                int e=temporary.front();
                rouge.push_back(e);
                anteriority[timeCounter].push_back(e);
                auto it=vert.begin();
                while((*it)!=e){it++;}
                vert.erase(it);

            }
            /*auto it3=rouge.begin();
            while(it3!=rouge.end()){
                std::cout<<(*it3)<<std::endl;
                it3++;
            }*/
        
    
     
        

       
            if(timeCounter>=4)
            {   
                if(timeCounter==4)
                {
                    noir.push_back(beginning_of_fire);
                    auto it=rouge.begin();
                    while((*it)!=beginning_of_fire){it++;}
                    rouge.erase(it);
                }
                else if (anteriority[timeCounter-4].size()==1)
                {
                    noir.push_back(anteriority[timeCounter-4].front());
                    auto it=rouge.begin();
                    while((*it)!=anteriority[timeCounter-4].front()){it++;}
                    rouge.erase(it);            
                }
                else
                {
                    int g=0;
                    int h=rand()%(anteriority[timeCounter-4].size()-1);
                    std::cout<<"nb pixel to color " << h+1 <<"/"<<anteriority[timeCounter-4].size()<< std::endl;

                    while (g<=h)
                    {
                        //std::cout<<"ok"<<std::endl;
                        int r=rand()%(anteriority[timeCounter-4].size()-1);
                        noir.push_back(anteriority[timeCounter-4].at(r));
                        auto it20=rouge.begin();

                        while ((*it20)!=(anteriority[timeCounter-4].at(r)))
                        {
                            it20++;
                        }

                        rouge.erase(it20);
                        auto it6=anteriority[timeCounter-4].begin();

                        while ((*it6)!=(anteriority[timeCounter-4].at(r)))
                        {
                            it6++;
                        }

                        anteriority[timeCounter-4].erase(it6);
                        //std::cout<<"ok2"<<std::endl;
                        g++;
                     }

                    if(anteriority[timeCounter-4].size()!=0)
                    {
                        anteriority[timeCounter-3].insert(anteriority[timeCounter-3].end(),anteriority[timeCounter-4].begin(),anteriority[timeCounter-4].end());
                    }
                   
                }
            
                
            }
        }
        
    }
    else if((y==0)&&(d!=DrillSize))
    {
        std::cout<< "Toute la forêt brûle :("<<std::endl;

        if (anteriority[timeCounter-4].size()==1)
        {
            noir.push_back(anteriority[timeCounter-4].front());
            auto it=rouge.begin();
            while((*it)!=anteriority[timeCounter-4].front()){it++;}
            rouge.erase(it);        
            auto it6=anteriority[timeCounter-4].begin();
            while ((*it6)!=(anteriority[timeCounter-4].front()))
            {
                it6++;
            }
            anteriority[timeCounter-4].erase(it6);
    
        }
        else
        {
            int g=0;
            int h=rand()%(anteriority[timeCounter-4].size()-1);
            std::cout<<"nb pixel to color " << h+1 <<"/"<<anteriority[timeCounter-4].size()<< std::endl;

            while (g<=h)
            {
                
                int r=rand()%(anteriority[timeCounter-4].size()-1);
                noir.push_back(anteriority[timeCounter-4].at(r));
                auto it20=rouge.begin();

                while ((*it20)!=(anteriority[timeCounter-4].at(r)))
                {
                    it20++;
                }
                rouge.erase(it20);

                auto it6=anteriority[timeCounter-4].begin();
                while ((*it6)!=(anteriority[timeCounter-4].at(r)))
                {
                    it6++;
                }
                anteriority[timeCounter-4].erase(it6);

                g++;
            }

            if(anteriority[timeCounter-4].size()!=0)
            {
                anteriority[timeCounter-3].insert(anteriority[timeCounter-3].end(),anteriority[timeCounter-4].begin(),anteriority[timeCounter-4].end());
            }
        }
    }
    else
    {
        std::cout<<"La feu a laissé place à un amas de cendre.";    
    }
    
    timeCounter=timeCounter+1;
    //std::cout<<"ok3"<<std::endl;
}

void FireSimulator::TimeEvolution(int n)
{
    while (timeCounter<n)
    {
        this->TimeScrolling();
    }
    
}

int FireSimulator::Access_At_The_Beginning_Of_The_Fire()
{
    return beginning_of_fire;
}

void FireSimulator::TimeReboot ()
{

}


Image FireSimulator::Image_Of_The_Moment()
{
    Image ImageResult(copy_of_width,copy_of_height);
           
    for (int n=0;n<copy_of_height;n++)
    {
        for(int k=0;k<copy_of_width;k++)
        {
            ImageResult.setPixel(n+1,k+1,Copy_of_Two_Dimensional_Table[n][k]);
        }
    }

    //int a=0;
    int  b=rouge.size();
    for(int a=0;a<b;a++)
    {
        std::pair<int,int> p=ImageResult.toCoordinate(rouge[a]);
        ImageResult.setPixel(p.first,p.second,Color::Red); 
    }

    int  c=noir.size();
    for(int a=0;a<c;a++)
    {
        std::pair<int,int> p=ImageResult.toCoordinate(noir[a]);
        ImageResult.setPixel(p.first,p.second,Color::Black);
    }


    return ImageResult;
}

