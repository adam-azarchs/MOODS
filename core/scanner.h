#ifndef MOODS_SCANNER_H
#define MOODS_SCANNER_H

#include "moods.h"
#include "motif.h"
#include "moods_misc.h"
#include "match_types.h"

#include <memory>

namespace MOODS { namespace scan{
    
    struct scanner_output
    {
        double score;
        std::size_t matrix;
        bool full;
    };

    struct state
    {
        vector<size_t> vs;
        const std::string prefix;
        //size_t first_required_index;
        size_t seq_start_pos;
        size_t variant_start_pos;
    };
    
    class Scanner {
    public:
        Scanner(unsigned int window_size);
        Scanner(unsigned int window_size, const std::vector<std::string>& alphabet);

        // void set_motifs(const std::vector<MOODS::scan::Motif>& motifs);
        void set_motifs(const std::vector<score_matrix>& matrices,
                        const std::vector<double>& bg,
                        const std::vector<double> thresholds);

        std::vector<std::vector<match> > scan(const std::string& s);
        std::vector<std::vector<match> > scan_max_hits(const std::string& s, size_t max_hits);

        size_t size(){
            if (!initialised)
                return 0;
            return motifs.size();
        }

        std::vector<std::vector<match_with_variant> > variant_matches(const std::string& seq, const std::vector<variant> variants);

    private:
        // std::vector<MOODS::scan::Motif> motifs;
        std::vector<std::unique_ptr<MOODS::scan::Motif> > motifs;
        std::vector<std::vector<scanner_output> > window_hits;
        unsigned int a;
        unsigned int l;
        std::vector<unsigned char> alphabet_map;
        bool initialised = false;
        unsigned int max_motif_size = 0;

        void initialise_hit_table();
        template<typename T> void process_matches(const std::string& s, T& match_handler);        
        void variant_matches_recursive(std::vector<std::vector<match_with_variant> >& results, const state& current,
                                                const std::string& seq, const std::vector<variant> variants);
    };
}}

#endif