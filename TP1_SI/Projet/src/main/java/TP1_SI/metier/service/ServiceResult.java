package TP1_SI.metier.service;

/**
 * @param <Result_t>
 * @param <ErrorEnum_t>
 * @author B3330
 */
public class ServiceResult<Result_t, ErrorEnum_t> {
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
        return "ServiceResult{ result = '" + result.toString() + "', error_code = '" + error.toString() + "'}";
    }

    public Result_t result;
    public ErrorEnum_t error;
}
