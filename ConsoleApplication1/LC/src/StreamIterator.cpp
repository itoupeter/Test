
// boost
#include <boost/lambda/lambda.hpp>

// STL
#include <iterator>
#include <iostream>


namespace LC
{

    class StreamIterator
    {
    public:
        void foo()
        {
            std::cout << "Hello World!" << std::endl;
        }

        void bar()
        {
            using namespace boost::lambda;
            typedef std::istream_iterator<int> in;

            std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
        }
    };

} // namespace LC
