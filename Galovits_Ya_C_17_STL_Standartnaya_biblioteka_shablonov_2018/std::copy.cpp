
template<typename InputIterator, typename OutputIterator>
OutputIterator copy(InputIterator it, InputIterator end_it, OutputIterator out_it)
{
    for(; it != end_it; ++it, ++out_it)
    {
        *out_it = *it;
    }
    return out_it;
}
