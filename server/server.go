package main

import (
    "fmt"
    "io"
    "net/http"
    "strings"
    "github.com/tesinclair/house-controller2.0/server/utils"
    "log"
    "time"
)

func check(e error){
    if e != nil{
        panic(e)
    }
}

func validateClientMiddleware(next http.HandlerFunc) http.HandlerFunc{
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request){
        auth := r.Header.Get("Authorization")

        utils.Log(fmt.Sprintf("[SERVER LOG]: Request: %s %s %s %s\n", r.RemoteAddr, r.Method, r.URL, r.Proto))

        for k, val := range r.Header {
            for _, v := range val{
                utils.Log(fmt.Sprintf("[SERVER LOG]: Header: %q, Value: %q\n", k, v))
            }
        }

        if strings.Contains(auth, "Bearer "){
            token := utils.GetAuth()
            _, userToken, _ := strings.Cut(auth, " ")

            if token != userToken{
                http.Error(w, "Bad Token", http.StatusForbidden)
            } 

        }else{
            http.Error(w, "No Auth Provided", http.StatusForbidden)
        }
        next.ServeHTTP(w, r)
    })
}

func getToggle(w http.ResponseWriter, r *http.Request){
    body, err := io.ReadAll(r.Body)
    check(err)
}

func main(){

    server := &http.Server{
        Addr: "0.0.0.0:6767",
        ReadTimeout: 10 * time.Second,
        WriteTimeout: 10 * time.Second,
    }
    // Routes
    toggle := http.HandlerFunc(getToggle)
    http.HandleFunc("/toggle", validateClientMiddleware(toggle))

    log.Fatal(server.ListenAndServe())
}



