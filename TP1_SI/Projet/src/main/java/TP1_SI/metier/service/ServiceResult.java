package TP1_SI.metier.service;

import java.io.Serializable;

/**
 * Classe générique représentant le résultat d'un appel à une méthode d'un service.
 * Cette classe peut être utilisé comme type de retour pour fournir à la fois un résultat de type 'Result_t'
 * et un éventuel code d'erreur appartenant à l'énumératrion 'ErrorEnum_t'.
 * Ce méchanisme peut être préférable à l'utilisation d'exeptions car ficilite l'ajout d'informations sur une erreur
 * et peut être sérialisé (ce qui peut faciliter la création de services REST en serialisant directement en JSON cette
 * classe par exemple ;) )
 * @param <Result_t> type du résultat de l'appel
 * @param <ErrorEnum_t> type des codes d'erreur
 * @author B3330
 */
public class ServiceResult<Result_t, ErrorEnum_t> implements Serializable {

    public ServiceResult(Result_t result, ErrorEnum_t error) {
        this.result = result;
        this.error = error;
    }

    @Override
    public int hashCode() {
        return (result != null ? result.hashCode() : 0);
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof ServiceResult))
            return false;

        ServiceResult other = (ServiceResult)object;

        if ((this.result == null && other.result != null) || (this.result != null && !this.result.equals(other.result)))
            return false;
        if ((this.error == null && other.error != null) || (this.error != null && !this.error.equals(other.error)))
            return false;
        return true;
    }

    @Override
    public String toString() {
        if(result != null)
            return "ServiceResult{ result = '" + result + "', error_code = '" + error + "'}";
        else
            return "ServiceResult{ error_code = '" + error + "'}";
    }

    public Result_t result;
    public ErrorEnum_t error;
}
