////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Analyst.h"
#include<algorithm>



Analyst::Analyst(const Image& img)//ok
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

    for (int i=1; i <= img.height(); i++)
    {
        for (int j=1; j <= img.width(); j++)
        {
            std::list<int>* line;
            line= new std::list<int>;
            line->push_back(img.toIndex(i,j));
            Separator.push_back(line);///augmenter la taille de vector si height*width>Separator.capacity
        }  
    }
      
    int k=0;
    for (int i=1; i <= img.height(); i++)
    {
        for (int j=1; j < img.width(); j++)
        {
            int current_position=img.toIndex(i,j);
            int right_position=img.toIndex(i,j+1);
            if(img.getPixel(i,j).operator==(img.getPixel(i,j+1)))
            {
                k++;
                (*Separator[current_position]).merge(*(Separator[right_position]));
                Separator[right_position]=Separator[current_position];
            }
        }
    }




    int z=0;
    for (int i=1; i < img.height(); i++)
    {
        for (int j=1; j <= img.width(); j++)
        {
            int current_position=img.toIndex(i,j);
            int bottom_position=img.toIndex(i+1,j);
            if((img.getPixel(i,j).operator==(img.getPixel(i+1,j)))&&(Separator[current_position]!=Separator[bottom_position]))
            {
                z++;
                if((*Separator[bottom_position]).size()==1)
                {
                    (*Separator[current_position]).merge((*Separator[bottom_position]));
                    Separator[bottom_position]=Separator[current_position];
                } else if ((*Separator[current_position]).size()==1)
                {
                    (*Separator[bottom_position]).merge((*Separator[current_position]));
                    Separator[current_position]=Separator[bottom_position];
                } else
                {   
                    if ((*Separator[current_position]).size()>=(*Separator[bottom_position]).size())
                    { 
                        std::list<int> line((*Separator[bottom_position]));                            
                        (*Separator[current_position]).merge((*Separator[bottom_position]));
                        int i=1;
                        int r=line.size();
                        while(i<=r)
                        {
                            Separator[line.front()]=Separator[current_position];
                            line.pop_front();
                            i++;
                        }                              
                    }else
                    {
                        std::list<int> line((*Separator[current_position]));
                        (*Separator[bottom_position]).merge((*Separator[current_position]));
                        int i=1;
                        int r=line.size();
                        while(i<=r)
                        {
                            Separator[line.front()]=Separator[bottom_position];
                            line.pop_front();
                            i++;
                        }
                    }
                        
                }
                    
                    //Separator[bottom_position].assign(Separator[current_position].begin(),Separator[current_position].end());
                    //Separator[img.toIndex(i,j)].push_front(img.toIndex(i+1,j));
                    //Separator.erase(Separator.begin()+img.toIndex(i+1,j));
            }
        }
    }
    /*auto it=(*Separator.at(354)).begin();
      while(it!=(*Separator.at(354)).end())
      {
          std::cout<< (*it)<<std::endl;
          it++;
      }*/
        //std::cout<< "k : " << k << std::endl;
        //std::cout<< "z : " << z << std::endl;

     /* auto it=Separator.begin();
      int i=0;
      while(it!=(Separator.end()))
      //while(i!=10)
      {
          std::cout << "liste " << i << ":";
          std::list<int>::iterator it2=(*it)->begin();
          while (it2!=(*it)->end())
          {
              std::cout<<(*it2)<<" ";
              it2 ++;
          }
          
          std::cout<<std::endl;
          it++;
          i++;
      }*/
      
}

Analyst :: ~Analyst()//ok
{
    Separator.clear();
    for(int i=0;i<copy_of_height;i++)
    {
        delete[] Copy_of_Two_Dimensional_Table[i];
    }

     delete[] Copy_of_Two_Dimensional_Table;
    
}

bool Analyst::belongToTheSameZone(int i1, int j1, int i2, int j2)//ok
{
    Image test(copy_of_width,copy_of_height);
    return Separator[test.toIndex(i1,j1)]->front()==Separator[test.toIndex(i2,j2)]->front();
}

int Analyst::nbPixelsOfColor(Color c) const
{
    int result=0;
    Image test(copy_of_width,copy_of_height);
    std::vector<int> temporary;
    auto it=Separator.begin();
    while(it!=Separator.end())
    {
        std::pair<int,int> p=test.toCoordinate((*it)->front());
        if((std::find(temporary.begin(),temporary.end(),(*it)->front())==temporary.end())&&(Copy_of_Two_Dimensional_Table[p.first-1][p.second-1].operator==(c)))
        {
            temporary.push_back((*it)->front());
            result=result+(*it)->size();
        }
        it++;
    }
    return result;
}

int Analyst::nbZonesOfColor(Color c) const//ok
{  
    Image test(copy_of_width,copy_of_height);
    std::vector<int> temporary;
    auto it=Separator.begin();
    while(it!=Separator.end())
    {
        std::pair<int,int> p=test.toCoordinate((*it)->front());
        if((std::find(temporary.begin(),temporary.end(),(*it)->front())==temporary.end())&&(Copy_of_Two_Dimensional_Table[p.first-1][p.second-1].operator==(c)))
        {
            temporary.push_back((*it)->front());
        }

        it++;
    }

    return temporary.size();
}

int Analyst::nbZones() const//ok
{
    
    std::vector<int> temporary;///utiliser std::set
    auto it=Separator.begin();
    while(it!=Separator.end())
    {
        if(std::find(temporary.begin(),temporary.end(),(*it)->front())==temporary.end())
        {
            temporary.push_back((*it)->front());
        }

        it++;
    }

    return temporary.size();
}

Image Analyst::fillZone(int i, int j, Color c)
{
    Image newImage(copy_of_width,copy_of_height); 

    for (int n=0;n<copy_of_height;n++)
    {
        for(int k=0;k<copy_of_width;k++)
        {
            newImage.setPixel(n+1,k+1,Copy_of_Two_Dimensional_Table[n][k]);
        }
    }
    std::list<int> line(*Separator[newImage.toIndex(i,j)]);
    int w=1;
    int r=line.size();
    std::pair<int,int> p;
    while(w<=r)
    {
        p=newImage.toCoordinate(line.front());
        newImage.setPixel(p.first,p.second,c);
        line.pop_front();
        w++;
    }
    /*for(int o=1;o<=newImage.height();o++)
    {
        for(int p=1;p<=newImage.width();p++)
        {
            if(belongToTheSameZone(i,j,o,p))
            {
                newImage.setPixel(o,p,c);
            }
        }
    }*/
    return newImage; 
}

std::set<int> Analyst::zoneOfPixel(int i, int j)
{
    Image test(copy_of_width,copy_of_height);
    std::set<int> set;
    /*for(int o=1;o<=copy_of_height;o++)
    {
        for(int p=1;p<=copy_of_width;p++)
        {
            if(belongToTheSameZone(i,j,o,p))
            {
                set.insert(test.toIndex(o,p));
            }
        }
    }*/
    std::list<int> line(*Separator[test.toIndex(i,j)]);

    int w=1;
    int r=line.size();
    std::pair<int,int> p;
    while(w<=r)
    {
        set.insert(line.front());
        line.pop_front();
        w++;
    }

    return set;

}




