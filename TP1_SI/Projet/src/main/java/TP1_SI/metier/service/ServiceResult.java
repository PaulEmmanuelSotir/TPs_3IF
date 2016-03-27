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

    public Result_t result;
    public ErrorEnum_t error;
}
