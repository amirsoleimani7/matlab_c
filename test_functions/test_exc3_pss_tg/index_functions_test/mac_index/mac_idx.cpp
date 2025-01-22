#include "H_header.h"

using namespace std;
using namespace Eigen;


MatrixXd mac_pot, mac_con, ind_con, igen_con, ibus_con;
MatrixXd mac_int, ind_int, igen_int, mac_em_idx, mac_tra_idx, mac_sub_idx, mac_ib_idx, not_ib_idx;
int n_mac, n_em, n_tra, n_sub, n_ib, n_ib_em, n_ib_tra, n_ib_sub, n_mot, n_ig;

void mac_indx(MatrixXd& mac_con , MatrixXd&  mac_pot , int& n_mac) {

    n_mac = mac_con.rows();
    mac_pot = MatrixXd::Zero(n_mac, 15);

    MatrixXd pqpc_idx = (mac_con.col(22).array() == 0 && mac_con.col(23).array() == 0).cast<double>();

    if (pqpc_idx.sum() > 0) {
        for (int i = 0; i < pqpc_idx.rows(); ++i) {
            if (pqpc_idx(i, 0) == 1) {
                mac_con(i, 22) = 1;
                mac_con(i, 23) = 1;
            }
        }
    }


    int macmax = mac_con.col(0).maxCoeff(); //finding the max value in the first column
    
    mac_int = MatrixXd::Zero(macmax, 1);
    for (int i = 0; i < n_mac; ++i) {
        mac_int(round(mac_con(i, 0)) - 1, 0) = i + 1;
    }

    int n_tot = n_mac;
    int ngm = n_mac;
    n_mot = 0;
    n_ig = 0;

    if (ind_con.size() > 0) {
        n_mot = ind_con.rows();
        n_tot = n_mac + n_mot;
        ngm = n_tot;
        int motmax = ind_con.col(0).maxCoeff();
        ind_int = MatrixXd::Zero(motmax, 1);
        for (int i = 0; i < n_mot; ++i) {
            ind_int(round(ind_con(i, 0)) - 1, 0) = n_mac + i + 1;
        }
    }

    if (igen_con.size() > 0) {
        n_ig = igen_con.rows();
        n_tot = n_tot + n_ig;
        int igmax = igen_con.col(0).maxCoeff();
        igen_int = MatrixXd::Zero(igmax, 1);
        for (int i = 0; i < n_ig; ++i) {
            igen_int(round(igen_con(i, 0)) - 1, 0) = ngm + i + 1;
        }
    }

    // Check for types of generators
    n_ib = 0;
    n_ib_em = 0;
    n_ib_tra = 0;
    n_ib_sub = 0;
    not_ib_idx = MatrixXd::LinSpaced(n_mac, 1, n_mac);

    if (ibus_con.size() > 0) {
        mac_ib_idx = (ibus_con.array() == 1).cast<double>();
        not_ib_idx = (ibus_con.array() == 0).cast<double>();
        n_ib = mac_ib_idx.sum();
    }

    mac_em_idx = (mac_con.col(6).array() == 0).cast<double>();
    n_em = mac_em_idx.sum();

    mac_tra_idx = ((mac_con.col(6).array() != 0) && (mac_con.col(8).array() == 0)).cast<double>();
    n_tra = mac_tra_idx.sum();

    mac_sub_idx = (mac_con.col(8).array() != 0).cast<double>();
    n_sub = mac_sub_idx.sum();

    if (n_ib != 0) {
        MatrixXd ib_em = (mac_con(mac_ib_idx.cast<int>(), 6).array() == 0).cast<double>();
        if (ib_em.sum() > 0) {
            mac_ib_em = mac_ib_idx(ib_em.cast<int>());
            n_ib_em = ib_em.sum();
        }

        MatrixXd ib_tra = ((mac_con(mac_ib_idx.cast<int>(), 6).array() != 0) && (mac_con(mac_ib_idx.cast<int>(), 8).array() == 0)).cast<double>();
        if (ib_tra.sum() > 0) {
            mac_ib_tra = mac_ib_idx(ib_tra.cast<int>());
            n_ib_tra = ib_tra.sum();
        }

        MatrixXd ib_sub = (mac_con(mac_ib_idx.cast<int>(), 8).array() != 0).cast<double>();
        if (ib_sub.sum() > 0) {
            mac_ib_sub = mac_ib_idx(ib_sub.cast<int>());
            n_ib_sub = ib_sub.sum();
        }
    }
}

