class MyParsingError : public std::exception {
public:
    explicit MyParsingError(const std::string& msg) : msg_(msg) {
        std::cout << msg << std::endl;
    }

    const char * what () const throw ()
    {
        return msg_.c_str();
    }

    std::string getMessage() const {return(msg_);}
private:
    std::string msg_;

};
