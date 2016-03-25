/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package TP1_SI.metier.service;

/**
 *
 * @author pesotir
 * @param <Result_t>
 * @param <ErrorEnum_t> 
 */
public class ServiceResult<Result_t, ErrorEnum_t> {
    public ServiceResult(Result_t result, ErrorEnum_t error)
    {
        this.result = result;
        this.error = error;
    }
    
    public Result_t result;
    public ErrorEnum_t error;
}
