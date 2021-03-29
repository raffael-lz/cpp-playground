void g(); // global linkage, declaration

namespace
{
void bf() // everything in unnamed namespace has local scope
{
    std::cout << "calling bf()" << std::endl;
}
} // namespace
