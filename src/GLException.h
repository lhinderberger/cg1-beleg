#ifndef CG1_GLEXCEPTION_H
#define CG1_GLEXCEPTION_H

#include <stdexcept>
#include <string>

namespace cg1 {
    class GLException : public std::runtime_error {
    private:
        std::string extendedMessage;

    public:
        GLException();

        virtual const char * what() const noexcept;
    };
}

#endif
