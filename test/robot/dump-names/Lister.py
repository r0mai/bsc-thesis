from __future__ import print_function
from robot.api import SuiteVisitor

class Lister(SuiteVisitor):
    def __init__(self, outputfile='/dev/stderr'):
        self.__output = open(outputfile, 'w')
        self.__levels = [
            'section',
            'subsection',
            'subsubsection',
            'paragraph',
            'subparagraph'
        ]

    def visit_suite(self, suite, level=0):
        self._write_heading(level, suite.name)
        if (len(suite.tests) > 0):
            self._write_line('List of tests:')
            self._write_line('\\begin{itemize}')
        for test in suite.tests:
            self._write_line('\\item', test.name)
            self._write_line()
            self._write_line(test.doc.encode('utf-8').decode('unicode_escape'))
            for keyword in test.keywords:
                self._write_line()
                self._write_line(
                    '{\\footnotesize \\ttfamily',
                    self._sanitize(keyword.name), '}')
        if (len(suite.tests) > 0):
            self._write_line('\\end{itemize}')

        for suite in suite.suites:
            assert(level < len(self.__levels))
            self.visit_suite(suite, level+1)


    def _sanitize(self, string):
        return string.replace('_', '\\_'). \
            replace('$', '\\$'). \
            replace('{', '\\{'). \
            replace('}', '\\}') \

    def _write_line(self, *args):
        print(*args, file=self.__output)

    def _write_heading(self, level, title):
        self._write_line('\\' + self.__levels[level] + '{' + title + '}')
