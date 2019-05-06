#include "cpp/SharedPointer/SharedPointer.hh"

#include <iostream>
#include <string>
#include <vector>

int main()
{
  using Data = std::vector<int>;

  // Default constructor. 
  {
    std::cout<<"\nTest Default Constructor"<<std::endl;
    Utility::SharedPointer<Data> sp;
    std::cout<<"Use count: "<<sp.use_count()<<std::endl;
    
    try
    {
      *sp;
    }
    catch(std::exception& e)
    {
      std::cout<<e.what()<<std::endl;
    }

    try
    {
      sp->size();
    }
    catch(std::exception& e)
    {
      std::cout<<e.what()<<std::endl;
    }
  }

  // Copy constructor.
  {
    std::cout<<"\nTest Copy Constructor"<<std::endl;
    auto sp1 = Utility::make_shared<Data>(std::initializer_list<int>{1, 2, 3});
    std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
    std::cout<<(*sp1)[0]<<std::endl;
    std::cout<<sp1->size()<<std::endl;
    
    {
      auto sp2 = sp1;
      std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
      std::cout<<"Use count: "<<sp2.use_count()<<std::endl;
      std::cout<<(*sp2)[0]<<std::endl;
      std::cout<<sp2->size()<<std::endl;
    }

    std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
  }

  // Copy Assignment.
  {
    std::cout<<"\nTest Copy Assignment"<<std::endl;
    auto sp1 = Utility::make_shared<Data>(std::initializer_list<int>{1, 2, 3});
    std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
    std::cout<<(*sp1)[0]<<std::endl;
    std::cout<<sp1->size()<<std::endl;

    {
      Utility::SharedPointer<Data> sp2;
      sp2 = sp1;
      std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
      std::cout<<"Use count: "<<sp2.use_count()<<std::endl;
      std::cout<<(*sp2)[0]<<std::endl;
      std::cout<<sp2->size()<<std::endl;
    }

    std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
  }

  // Move constructor.
  {
    std::cout<<"\nTest Move Constructor"<<std::endl;
    auto sp1 = Utility::make_shared<Data>(std::initializer_list<int>{1, 2, 3});
    std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
    std::cout<<(*sp1)[0]<<std::endl;
    std::cout<<sp1->size()<<std::endl;
    
    auto sp2 = std::move(sp1);
    std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
    std::cout<<"Use count: "<<sp2.use_count()<<std::endl;
    std::cout<<(*sp2)[0]<<std::endl;
    std::cout<<sp2->size()<<std::endl;
  }

  // Move Assignment.
  {
    std::cout<<"\nTest Move Assignment"<<std::endl;
    auto sp1 = Utility::make_shared<Data>(std::initializer_list<int>{1, 2, 3});
    std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
    std::cout<<(*sp1)[0]<<std::endl;
    std::cout<<sp1->size()<<std::endl;

    Utility::SharedPointer<Data> sp2;
    sp2 = std::move(sp1);
    std::cout<<"Use count: "<<sp1.use_count()<<std::endl;
    std::cout<<"Use count: "<<sp2.use_count()<<std::endl;
    std::cout<<(*sp2)[0]<<std::endl;
    std::cout<<sp2->size()<<std::endl;
  }

  return 0;
}

