#pragma once
#include <memory>
#include <array>
#include <pulsar_libint/pulsar_libint.hpp>
#include <pulsar/modulebase/TwoCenterIntegral.hpp>
#include <libint2.hpp>


namespace pulsar_libint {

template<libint2::Operator Op>
class LibInt2C : public pulsar::TwoCenterIntegral {
protected:
    std::array<libint2::BasisSet,2> bs_;
    libint2::Engine engine_;
public:
     LibInt2C(ID_t id):TwoCenterIntegral(id)
     {
        libint2::initialize();
     }

    ~LibInt2C()
    {
        libint2::finalize();
    }

     void initialize_(unsigned int deriv,
                      const pulsar::Wavefunction &,
                      const pulsar::BasisSet & bs1,
                      const pulsar::BasisSet & bs2)
     {

       bs_=std::array<libint2::BasisSet,2>({make_basis(bs1),make_basis(bs2)});
       const size_t max_prims=std::max(bs_[0].max_nprim(bs_[0]),
                                       bs_[1].max_nprim(bs_[1]));
       const size_t max_l=std::max(bs_[0].max_l(bs_[0]),
                                   bs_[1].max_l(bs_[1]));

       engine_=libint2::Engine(Op,max_prims,max_l,deriv);
     }

     const double* calculate_(uint64_t shell1, uint64_t shell2)
     {
         const auto& buf_vec=engine_.results();
         engine_.compute(bs_[0][shell1],bs_[1][shell2]);
         return buf_vec[0];
     }

};

using Kinetic=LibInt2C<libint2::Operator::kinetic>;
using Overlap=LibInt2C<libint2::Operator::overlap>;

struct NuclearElectron: public LibInt2C<libint2::Operator::nuclear> {
    using base_type=LibInt2C<libint2::Operator::nuclear>;

    NuclearElectron(ID_t id):base_type(id){}

    void initialize_(unsigned int deriv,
                     const pulsar::Wavefunction &wfn,
                     const pulsar::BasisSet & bs1,
                     const pulsar::BasisSet & bs2)
    {
        base_type::initialize_(deriv,wfn,bs1,bs2);
        std::vector<std::pair<double,std::array<double,3>>> qs;
        for(const auto& ai: *wfn.system)
            qs.push_back({ai.charge==0? ai.Z: ai.charge ,{ai[0],ai[1],ai[2]}});
        engine_.set_params(qs);
    }

};

struct Metric: public LibInt2C<libint2::Operator::coulomb> {
    using base_type=LibInt2C<libint2::Operator::coulomb>;

    Metric(ID_t id):base_type(id){}

    void initialize_(unsigned int deriv,
                     const pulsar::Wavefunction &wfn,
                     const pulsar::BasisSet &bs1,
                     const pulsar::BasisSet &bs2)
    {
         base_type::initialize_(deriv,wfn,bs1,bs2);
         engine_.set_braket(libint2::BraKet::xs_xs);
    }
};

}//End namespace
