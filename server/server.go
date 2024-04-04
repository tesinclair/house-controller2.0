package main

import (
    "errors"
    "fmt"
    "io"
    "net/http"
    "os"
    "strings"
    "server/serverlib/getAuth"
)

func check(e error){
    if e != nil{
        panic(e)
    }
}

func validateClientMiddleware(next http.Handler) http.Handler{
    return http.HandlerFunc(func(w, http.ResponseWriter, r *http.Request){
        auth, err := head.Header.Get("Authorization")
        check(err)
        if strings.Contains(auth, "Bearer "){
            token = getAuth();
            userToken = strings.Cut(auth, " ")

            if !hashedToken == userToken{
                return
            }else{
                w.WriteHeader(http.StatusForbidden)
                w.Write([]byte("403 - Incorrect Auth token")
            }
        }else{
            w.WriteHeader(http.StatusForbidden)
            w.Write([]byte("403 - No Auth token Provided")
        }
        next.ServeHttp(w, r)
    }
}

func getToggle(w http.ResponseWriter, r *http.Request){
    body, err := io.ioutil.ReadAll(r.Body)
    check(err)
    fmt.Prinf("body: %s\n", body)
}

func main(){

    server := &http.Server{
        Addr: "0.0.0.0:6758",
        ReadTimeout: 10 * time.Second,
        WriteTimeout: 10 * time.Second,
    }
    // Routes
    toggle := http.HandlerFunc(getToggle)
    http.HandleFunc("/toggle", validateClientMiddleware(toggle))

    log.Fatal(server.ListenAndServe())




