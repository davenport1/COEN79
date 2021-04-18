
#include <iostream>
#include <cmath>
#include <string.h>
#include <climits>
#include "poly.h"
#include "assert.h"


namespace coen79_lab5 {

    polynomial::polynomial(double c ,unsigned int exponent){
        size =0;
        current_degree=0;
        poly = NULL;
        reserve(exponent+1);
        poly[exponent] = c;
    }
    polynomial::polynomial(const polynomial& source){//mb this??
        size =source.size;
        poly = new double[size];
        for(int i=0;i<size;i++){
            poly[i]=source.poly[i];
        }
        current_degree = source.current_degree;
    }
    polynomial::~polynomial(){
        //destructor
        delete[] poly;
    }

    void polynomial::update_current_degree(){
        for(int i=0;i<size;i++){
            if(poly[i] !=0){
                current_degree = i;
            }
        }
    }
    void polynomial::reserve(size_t number){//unsigned int exponent RESERVE SIZE NOT EPXONENT
       if(number >size){
           double *temp = poly;
           size = number;
           poly = new double[size];
            for(int i=0;i<size;i++){
                poly[i]=0;
            }
            if(temp!=NULL){
                for(int i = 0;i<=current_degree;i++){
                    poly[i] = temp[i];
                }
                delete[] temp;
            }
            current_degree= number-1;
       }
    }
    void polynomial::trim(){
        if(degree()!=0)
        {
         double *temp = new double[degree() +1];
         std::copy(poly,poly+degree()+1,temp);
            delete[] poly;
            poly= temp;
            size = degree()+1;
        }
        else if(degree()==0)
        {
            delete[]poly;
        }
    }
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
        if(exponent>current_degree){
            reserve(exponent+1);
        }
        poly[exponent] = coefficient;
        update_current_degree();
    }
    void polynomial::add_to_coef(double amount, unsigned int exponent){
        if(exponent>current_degree){
            reserve(exponent+1);
        }
        poly[exponent] += amount;
        update_current_degree();

    }
    void polynomial::clear( ){
         for(int i = 0; i < size; ++i) {
            poly[i] = 0;
        }
        current_degree = 0;
    }

    polynomial& polynomial::operator =(const polynomial& source){
        if(this!=&source){
            delete []poly;
            poly = new double[source.size];
            current_degree=source.current_degree;
            size= source.size;
            for(int i = 0;i<size;i++){
                poly[i] = source.poly[i];
            }
        }
        return *this;
    }
    polynomial& polynomial::operator =(double c){
           clear();
           poly[0]=c;

           return *this;
    }
    polynomial polynomial::antiderivative( ) const{//check
        polynomial antiderivative;
        for(int i = (degree() + 1); i > 0; --i) {
            if(i != 0) {
                antiderivative.assign_coef((this->poly[i - 1])/i, i);
            }
        }
        return antiderivative;

    }
    double polynomial::coefficient(unsigned int exponent) const{
        if(exponent > current_degree) {
            return 0;
        }
        return poly[exponent];

    }
    double polynomial::definite_integral(double x0, double x1) const{
        // polynomial antiderivative = this->antiderivative();
        // double sumx1 = 0;
        // double sumx0 = 0;
        // for(int i = 0; i < antiderivative.degree(); ++i) {
        //     sumx1 += (antiderivative.coefficient(i) * (pow(x1, i)));
        //     sumx0 += (antiderivative.coefficient(i) * (pow(x0, i)));
        // }
        // return sumx1 - sumx0;
        return(antiderivative().eval(x1) - antiderivative().eval(x0));
    }

    polynomial polynomial::derivative( ) const{
        polynomial derivative;
        for(int e = 0; e < current_degree; ++e) {
            derivative.assign_coef(poly[e + 1] * (e + 1), e);
        }
        return derivative;
    }
    double polynomial::eval(double x) const{
           double sum = 0;
        for(int e = 0; e <= current_degree; ++e) {
            if(poly[e] != 0) {
                sum += (poly[e] * pow(x,e));
            }
        }
        return sum;

    }
    bool polynomial::is_zero( ) const{
         return(degree() == 0 && poly[0]==0);
    }
    unsigned int polynomial::next_term(unsigned int e) const{
         ++e;
        while(e < current_degree + 1) {
            if(poly[e] != 0) {
                return e;
            }
            ++e;
        }
        return 0;
    }
    unsigned int polynomial::previous_term(unsigned int e) const{

        for(int i = e-1; i >= 0; --i) {
            if(poly[i] != 0) {
                return i;
            }
        }
        return UINT_MAX;

    }
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        polynomial p3;

        for(int i=0;i<=p1.degree();i++){
            p3.add_to_coef(p1.coefficient(i),i);
        }
        for(int i=0;i<=p2.degree();i++){
              p3.add_to_coef(p2.coefficient(i),i);
        }
        return p3;
    }
    polynomial operator -(const polynomial& p1, const polynomial& p2){
        polynomial p3;

        for(int i=0;i<=p1.degree();i++){
            p3.add_to_coef(p1.coefficient(i),i);
        }
        for(int i=0;i<=p2.degree();i++){
              p3.add_to_coef(-p2.coefficient(i),i);
        }
        return p3;
    }
    polynomial operator *(const polynomial& p1, const polynomial& p2){
        polynomial p3;
        for(int i=0;i<=p1.degree();i++){
            for(int j=0;j<=p2.degree();j++){
                p3.add_to_coef(p1.coefficient(i)*p2.coefficient(j),i+j);
            }
        }
        return p3;
    }

     std::ostream& operator << (std::ostream& out, const polynomial& p){
     int e = p.degree();
        if(e > 0) {
            out <<  p.coefficient(e) << "x^" << e << " ";
            e = p.previous_term(e);
            while(e != UINT_MAX) {
                if(e > 1) {
                    if(p.coefficient(e) < 0) {
                        out << " - " << (p.coefficient(e) * -1) << "x^" << e;
                    }
                    else {
                        out << " + " << p.coefficient(e) << "x^" << e;
                    }
                }
                else if (e == 1) {
                    if(p.coefficient(e) < 0) {
                        out << " - " << (p.coefficient(e) * -1) << "x";
                    }
                    else {
                        out << " + " << p.coefficient(e) << "x";
                    }
                }
                e = p.previous_term(e);
            }
        }
        if(p.coefficient(0) < 0) {
            out << " - " << (p.coefficient(0) * -1);
        }
        else if (p.coefficient(0) > 0) {
            out << " + " << p.coefficient(0);
        }
        return out;
    }



}