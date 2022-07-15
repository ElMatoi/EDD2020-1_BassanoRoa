#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <iomanip>

#include "Detector.hpp"
#include "Persona.hpp"
#include "kdTree.hpp"
#include "kdTreeNode.hpp"
//#include "ListaPersonas.hpp"
//#include "Nodo.hpp"
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    int contadorEntran = 0;
    int contadorSalen = 0;
      kdTree *arbolito = new kdTree(); // declara el tree

    Detector detector;
    char *filepath = new char[200];

    detector.toggleMode();
    cout << detector.modeName() << endl;
   

    for (int i = 1; i <= 3; i++)
    {

        sprintf(filepath, "C:/Users/Usuario/Desktop/passgeway/%d.jpg", i);
        Mat imagen = imread(filepath);

        vector<Persona> found = detector.detect(imagen);
        for (vector<Persona>::iterator j = found.begin(); j != found.end(); ++j)
        {
            Persona &p = *j;
            // cout << "(" << p.getXComienzo() << ", " << p.getYComienzo() << ")" << endl;
            // detector.adjustRect(r);
            rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(255, 0, 0), 2);
            circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(255, 0, 0), 3);
            circle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), 3, cv::Scalar(255, 0, 255), 2);
            circle(imagen, cv::Point(p.getXFin(), p.getYFin()), 3, cv::Scalar(0, 255, 255), 2);

           


         
            kdTreeNode *nodos = new kdTreeNode(p.getXCentro(), p.getYCentro());
                if(arbolito->getRoot()==NULL){
                    // si el root es ==null, se ingresa la primera cordenada como raiz
                   
                     arbolito->insert(nodos);// se ingresa como raiz del arbol
                     nodos->setYInicial(p.getYCentro());
                     cout<<("nodosNueevos1")<<endl;
                     cout<<(nodos->getY())<<endl;
                     cout<<(nodos->getYInicial())<<endl;
                    


                     

                }else if(arbolito->getRoot()!=NULL){
                    
                   kdTreeNode *NodoMascercano=arbolito->findClosestPoint(nodos); 
                   double distancia= NodoMascercano->findDistanceBetweenTwoPoints( nodos, NodoMascercano);
                   
                   if(distancia>=0.5){ // si la distancia es menor a 1,0, se considera un nuevo punto
                    arbolito->insert(nodos);
                    nodos->setYInicial(p.getYCentro());
                    cout<<("nodosNueevos2")<<endl;
                    cout<<(nodos->getYInicial())<<endl;
                    cout<<(nodos->getY())<<endl;


                   }else if(distancia<0.5){

                    NodoMascercano->setX(p.getXCentro());
                    NodoMascercano->setY(p.getYCentro());
                     if(NodoMascercano->getYInicial()>180 && NodoMascercano->getY()<180){
                        contadorSalen++;

                     }else if(NodoMascercano->getYInicial()<180 && NodoMascercano->getY()>180){
                        contadorEntran++;
                     }
                     cout<<("nodosAntiwosXD")<<endl;
                    cout<<(NodoMascercano->getYInicial())<<endl;
                    cout<<(NodoMascercano->getY())<<endl;

                   }




                }
            

           /* if (arbolito->getRoot()->getY() > imagen.rows/2 || arbolito->getRoot()->getLeft()->getY()>imagen.rows/2 || arbolito->getRoot()->getRight()->getY() > imagen.rows/2  )
            {
                contadorEntran = contadorEntran + 1;
            }
            else if (arbolito->getRoot()->getY() < imagen.rows/2 || arbolito->getRoot()->getLeft()->getY()<imagen.rows/2 || arbolito->getRoot()->getRight()->getY() < imagen.rows/2 )
            {
                contadorSalen = contadorSalen + 1;
            }*/
        }

        // cout << "(" << imagen.rows / 2 << ", " << imagen.cols / 2 << ")" << endl;
        line(imagen, Point(0, imagen.rows / 2), Point(2000, imagen.cols / 2), Scalar(255,0,0), 2, 8, 0);
       
        imshow("People detector", imagen);
        waitKey(1000);
    }
    //arbolito->print();
      cout <<"Entraron:"<< contadorEntran << endl;
     cout << "Salieron:"<<contadorSalen << endl;
     double vEntran=contadorEntran*0.360;
     double  vSalen=contadorSalen*0.360;
     cout <<"Flujo entrada promedio:"<<vEntran<< endl;

     cout <<"Flujo salida promedio:"<<vSalen<<endl;
    
  
    return 0;
}




 

    /*double distancia2Puntos(int p1x, int p1y, int p2x, int p2y){


        int a, b;
        a = p1y - p2y;
        b = p1x - p2x;
        return sqrtf(a * a + b * b);
    }*/
     /* kdTreeNode *NodoMascercano=arbolito->findClosestPoint(nodos); 

            arbolito->insert(NodoMascercano);

            arbolito->print();//

            /* Nodo *nuevo = new Nodo(p);
             int cant = lp.insertar(nuevo);

             for (int j = 0; j <= cant; j++)
             {
                 points[p.getXComienzo(), p.getYComienzo()][i] = 0;
             }*/
