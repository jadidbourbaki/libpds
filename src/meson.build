
probability_sources = ['bloom.c', 'cms.c', 'pt_bloom.c', 'hash.c']
probability_lib = static_library('libprobability', probability_sources)

test_bloom = executable('test_bloom', 'bloom_test.c', link_with: probability_lib)
test('test_bloom', test_bloom) 

test_cms = executable('test_cms', 'cms_test.c', link_with: probability_lib)
test('test_cms', test_cms)

test_pt_bloom = executable('test_bt_bloom', 'pt_bloom_test.c', link_with: probability_lib)
test('test_pt_bloom', test_pt_bloom)
