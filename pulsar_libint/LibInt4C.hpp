#pragma once
#include <memory>
#include <array>
#include <limits>
#include <pulsar_libint/pulsar_libint.hpp>
#include <pulsar/modulebase/FourCenterIntegral.hpp>
#include <pulsar/datastore/OptionMap.hpp>
#include <libint2.hpp>


namespace pulsar_libint {

inline size_t get_max(size_t v1,size_t v2, size_t v3, size_t v4){
    return std::max(std::max(std::max(v1,v2),v3),v4);
}

template<libint2::Operator Op>
class LibInt4C : public pulsar::FourCenterIntegral {
private:
    std::array<libint2::BasisSet,4> bs_;
    libint2::Engine engine_;
public:
     LibInt4C(ID_t id):FourCenterIntegral(id)
     {
        libint2::initialize();
     }

    ~LibInt4C()
    {
        libint2::finalize();
    }

     HashType my_hash_(unsigned int deriv,
                       const pulsar::Wavefunction& wfn,
                       const pulsar::BasisSet& bs1,
                       const pulsar::BasisSet& bs2,
                       const pulsar::BasisSet& bs3,
                       const pulsar::BasisSet& bs4)
     {
         auto opt_key=(options().has_key("THRESHOLD")?
                bphash::hash_to_string(options().hash_values(std::set<std::string>({"THRESHOLD"})))
                         :"");
         return bphash::hash_to_string(bs1.my_hash())+
                 bphash::hash_to_string(bs2.my_hash())+
                 bphash::hash_to_string(bs3.my_hash())+
                 bphash::hash_to_string(bs4.my_hash())+
                 opt_key;
     }

     void initialize_(unsigned int deriv,
                      const pulsar::Wavefunction &,
                      const pulsar::BasisSet & bs1,
                      const pulsar::BasisSet & bs2,
                      const pulsar::BasisSet & bs3,
                      const pulsar::BasisSet & bs4)
     {

       bs_=std::array<libint2::BasisSet,4>({make_basis(bs1),
                                            make_basis(bs2),
                                            make_basis(bs3),
                                            make_basis(bs4)});
       const size_t max_prims=get_max(bs_[0].max_nprim(bs_[0]),
                                      bs_[1].max_nprim(bs_[1]),
                                      bs_[2].max_nprim(bs_[2]),
                                      bs_[3].max_nprim(bs_[3]));
       const size_t max_l=get_max(bs_[0].max_l(bs_[0]),
                                  bs_[1].max_l(bs_[1]),
                                  bs_[2].max_l(bs_[2]),
                                  bs_[3].max_l(bs_[3]));
       const bool has_key= options().has_key("THRESHOLD");
       const pulsar::OptionMap& opt=options();
       double thresh(has_key ? opt.get<double>("THRESHOLD") :
                               std::numeric_limits<double>::epsilon());

       engine_=libint2::Engine(Op,max_prims,max_l,deriv,thresh);
     }

     const double* calculate_(uint64_t shell1, uint64_t shell2,
                              uint64_t shell3, uint64_t shell4)
     {
         const auto& buf_vec=engine_.results();
         engine_.compute(bs_[0][shell1],bs_[1][shell2],
                            bs_[2][shell3],bs_[3][shell4]);
         return buf_vec[0];
     }

};

using ERI=LibInt4C<libint2::Operator::coulomb>;

}//End namespace
