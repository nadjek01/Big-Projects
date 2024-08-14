Authors: Nana Adjekum and Henry Rees Tindall

Help Received: John Eastman and Bill from office hours were a huge help along
               with lecture notes and lab

Implementation: To our knowledge everything has been implemented correctly
                as the spec dictates other than the transpose of an image
                which was extra credit

Architecture: Our UArray2b is structured as a UArray2 of blocks that hold
              pointers to UArrays (1D) that hold the actual pixels. This was
              the simplest way to represent a block array because it is
              organized in a very straghtforward way with no unneccesary 
              complexity. Our Ppmtrans file uses Pnm_ppmread to create a 2D
              array of either type UArray2 or UArray2b (as dictated by mehods)
              and then calls applyRotation. ApplyRotation will either map 
              through the 2D array (with the map being dictated by methods)
              or if the rotation requires flipped dimensions it will call
              transform_diff_dim() which will handle the flipping of dimensions
              and mapping through the 2D array. Once the rotation is applied
              then we use Pnm_ppmwrite() to write to stdout and everything is
              freed

Time:
    We spent 40 hours on this homework assignment.
Measured Solutions:
Computer Stats:
    processor       : 0
    vendor_id       : GenuineIntel
    cpu family      : 6
    model           : 85
    model name      : Intel(R) Xeon(R) Silver 4214Y CPU @ 2.20GHz
    stepping        : 7
    microcode       : 0x5000029
    cpu MHz         : 2194.843
    cache size      : 16896 KB
    physical id     : 0
    siblings        : 6
    core id         : 0
    cpu cores       : 6
    apicid          : 0
    initial apicid  : 0
    fpu             : yes
    fpu_exception   : yes
    cpuid level     : 22
    wp              : yes
    flags           : fpu vme de pse tsc msr pae mce cx8 apic 
    sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2
     ss ht syscall nx pdpe1gb rdtscp lm constant_tsc 
     arch_perfmon nopl xtopology tsc_reliable nonstop_tsc 
     cpuid pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2
      x2apic movbe popcnt tsc_deadline_timer aes xsave 
      avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch
       cpuid_fault invpcid_single ssbd ibrs ibpb stibp 
       ibrs_enhanced fsgsbase tsc_adjust bmi1 hle avx2 
       smep bmi2 invpcid rtm mpx avx512f avx512dq rdseed
        adx smap clflushopt clwb avx512cd avx512bw 
        avx512vl xsaveopt xsavec xsaves arat pku ospke
         md_clear flush_l1d arch_capabilities
    bugs            : spectre_v1 spectre_v2 spec_store_bypass
     swapgs taa itlb_multihit mmio_stale_data retbleed eibrs_pbrsb
    bogomips        : 4389.68
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 43 bits physical, 48 bits virtual
    power management:

    processor       : 1
    vendor_id       : GenuineIntel
    cpu family      : 6
    model           : 85
    model name      : Intel(R) Xeon(R) Silver 4214Y CPU @ 2.20GHz
    stepping        : 7
    microcode       : 0x5000029
    cpu MHz         : 2194.843
    cache size      : 16896 KB
    physical id     : 0
    siblings        : 6
    core id         : 1
    cpu cores       : 6
    apicid          : 1
    initial apicid  : 1
    fpu             : yes
    fpu_exception   : yes
    cpuid level     : 22
    wp              : yes
    flags           : fpu vme de pse tsc msr pae mce cx8 apic sep 
    mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht 
    syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon nopl 
    xtopology tsc_reliable nonstop_tsc cpuid pni pclmulqdq ssse3 
    fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt 
    tsc_deadline_timer aes xsave avx f16c rdrand hypervisor
     lahf_lm abm 3dnowprefetch cpuid_fault invpcid_single
      ssbd ibrs ibpb stibp ibrs_enhanced fsgsbase tsc_adjust
       bmi1 hle avx2 smep bmi2 invpcid rtm mpx avx512f 
       avx512dq rdseed adx smap clflushopt clwb avx512cd
        avx512bw avx512vl xsaveopt xsavec xsaves arat pku
         ospke md_clear flush_l1d arch_capabilities
    bugs            : spectre_v1 spectre_v2 spec_store_bypass
     swapgs taa itlb_multihit mmio_stale_data retbleed eibrs_pbrsb
    bogomips        : 4389.68
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 43 bits physical, 48 bits virtual
    power management:

    processor       : 2
    vendor_id       : GenuineIntel
    cpu family      : 6
    model           : 85
    model name      : Intel(R) Xeon(R) Silver 4214Y CPU @ 2.20GHz
    stepping        : 7
    microcode       : 0x5000029
    cpu MHz         : 2194.843
    cache size      : 16896 KB
    physical id     : 0
    siblings        : 6
    core id         : 2
    cpu cores       : 6
    apicid          : 2
    initial apicid  : 2
    fpu             : yes
    fpu_exception   : yes
    cpuid level     : 22
    wp              : yes
    flags           : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr
                      pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss
                      ht syscall nx pdpe1gb rdtscp lm constant_tsc 
                      arch_perfmon nopl xtopology tsc_reliable nonstop_tsc
                      cpuid pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 
                      x2apic movbe popcnt tsc_deadline_timer aes xsave avx 
                      f16c rdrand hypervisor lahf_lm abm 3dnowprefetch 
                      cpuid_fault invpcid_single ssbd ibrs ibpb stibp 
                      ibrs_enhanced fsgsbase tsc_adjust bmi1 hle avx2 
                      smep bmi2 invpcid rtm mpx avx512f avx512dq rdseed 
                      adx smap clflushopt clwb avx512cd avx512bw avx512vl 
                      xsaveopt xsavec xsaves arat pku ospke md_clear 
                      flush_l1d arch_capabilities
    bugs            : spectre_v1 spectre_v2 spec_store_bypass swapgs 
                      taa itlb_multihit mmio_stale_data retbleed eibrs_pbrsb
    bogomips        : 4389.68
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 43 bits physical, 48 bits virtual
    power management:

    processor       : 3
    vendor_id       : GenuineIntel
    cpu family      : 6
    model           : 85
    model name      : Intel(R) Xeon(R) Silver 4214Y CPU @ 2.20GHz
    stepping        : 7
    microcode       : 0x5000029
    cpu MHz         : 2194.843
    cache size      : 16896 KB
    physical id     : 0
    siblings        : 6
    core id         : 3
    cpu cores       : 6
    apicid          : 3
    initial apicid  : 3
    fpu             : yes
    fpu_exception   : yes
    cpuid level     : 22
    wp              : yes
    flags           : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge 
    mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall nx pdpe1gb 
    rdtscp lm constant_tsc arch_perfmon nopl xtopology tsc_reliable 
    nonstop_tsc cpuid pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 
    x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand 
    hypervisor lahf_lm abm 3dnowprefetch cpuid_fault invpcid_single 
    ssbd ibrs ibpb stibp ibrs_enhanced fsgsbase tsc_adjust bmi1 hle 
    avx2 smep bmi2 invpcid rtm mpx avx512f avx512dq rdseed adx smap 
    clflushopt clwb avx512cd avx512bw avx512vl xsaveopt xsavec xsaves 
    arat pku ospke md_clear flush_l1d arch_capabilities
    bugs            : spectre_v1 spectre_v2 spec_store_bypass swapgs 
    taa itlb_multihit mmio_stale_data retbleed eibrs_pbrsb
    bogomips        : 4389.68
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 43 bits physical, 48 bits virtual
    power management:

    processor       : 4
    vendor_id       : GenuineIntel
    cpu family      : 6
    model           : 85
    model name      : Intel(R) Xeon(R) Silver 4214Y CPU @ 2.20GHz
    stepping        : 7
    microcode       : 0x5000029
    cpu MHz         : 2194.843
    cache size      : 16896 KB
    physical id     : 0
    siblings        : 6
    core id         : 4
    cpu cores       : 6
    apicid          : 4
    initial apicid  : 4
    fpu             : yes
    fpu_exception   : yes
    cpuid level     : 22
    wp              : yes
    flags           : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr
     pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall 
     nx pdpe1gb rdtscp lm constant_tsc arch_perfmon nopl xtopology 
     tsc_reliable nonstop_tsc cpuid pni pclmulqdq ssse3 fma cx16 
     pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer 
     aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch
      cpuid_fault invpcid_single ssbd ibrs ibpb stibp ibrs_enhanced
       fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 invpcid rtm mpx 
       avx512f avx512dq rdseed adx smap clflushopt clwb avx512cd 
       avx512bw avx512vl xsaveopt xsavec xsaves arat pku ospke 
       md_clear flush_l1d arch_capabilities
    bugs            : spectre_v1 spectre_v2 spec_store_bypass 
    swapgs taa itlb_multihit mmio_stale_data retbleed eibrs_pbrsb
    bogomips        : 4389.68
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 43 bits physical, 48 bits virtual
    power management:

    processor       : 5
    vendor_id       : GenuineIntel
    cpu family      : 6
    model           : 85
    model name      : Intel(R) Xeon(R) Silver 4214Y CPU @ 2.20GHz
    stepping        : 7
    microcode       : 0x5000029
    cpu MHz         : 2194.843
    cache size      : 16896 KB
    physical id     : 0
    siblings        : 6
    core id         : 5
    cpu cores       : 6
    apicid          : 5
    initial apicid  : 5
    fpu             : yes
    fpu_exception   : yes
    cpuid level     : 22
    wp              : yes
    flags           : fpu vme de pse tsc msr pae mce cx8 apic 
    sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2
     ss ht syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon
      nopl xtopology tsc_reliable nonstop_tsc cpuid pni pclmulqdq
       ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt
        tsc_deadline_timer aes xsave avx f16c rdrand hypervisor
         lahf_lm abm 3dnowprefetch cpuid_fault invpcid_single
          ssbd ibrs ibpb stibp ibrs_enhanced fsgsbase tsc_adjust
           bmi1 hle avx2 smep bmi2 invpcid rtm mpx avx512f 
           avx512dq rdseed adx smap clflushopt clwb avx512cd
            avx512bw avx512vl xsaveopt xsavec xsaves arat pku
             ospke md_clear flush_l1d arch_capabilities
    bugs            : spectre_v1 spectre_v2 spec_store_bypass
     swapgs taa itlb_multihit mmio_stale_data retbleed eibrs_pbrsb
    bogomips        : 4389.68
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 43 bits physical, 48 bits virtual
    power management:

To measure our solution to this homework we used the CPUTime program. We then
piped all the infomation from the file into a txt file as well as
information about the rotation and the image. We then used excel to
format this information into readable data. We came to the conclusion
that most of the time row major order was the quickest when
it came down to rotating each image. Our images in our measured
solutions differed in size so the biggest difference in time
was attributed to that. But in image, block major rotation
seemed to take as much as 2x the time as row and col major.
Row major was the best in most cases and col major
was behind that but only by a small margin (and this
often differed image from image). We have concluded
that this is because of our implementation, i.e. our
algorithm for UArray2b does not quite have the best
blocking (especially in this case where blocksize is calculated
behind the scenes and is not passed in) and we may not
be allocating memory that is contigous in memory because
of the smaller arrays being pointed to from the big array.

PLEASE LOOK AT MEASURED PERFORMANCE TABLE AND TIMEOUT.TXT!!!!
